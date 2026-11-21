# 4. RSA-PSS (Probabilistic Signature Scheme), implemented step by step
#    following RFC 8017 (PKCS #1 v2.2). Only hashlib and os.urandom are used.

import hashlib
import os
import random

H_LEN = 32                      # SHA-256 digest size
S_LEN = 32                      # salt length


def sha256(data):
    return hashlib.sha256(data).digest()


# --- key generation ---------------------------------------------------------

def gcd_ext(a, b):
    if b == 0:
        return a, 1, 0
    g, s1, t1 = gcd_ext(b, a % b)
    s = t1
    t = s1 - a // b * s
    return g, s, t


def mod_inverse(a, m):
    g, s, _ = gcd_ext(a, m)
    if g != 1:
        raise ValueError("not invertible")
    return s % m


def is_prime(n, rounds=40):
    ''' Miller-Rabin primality test. '''
    if n < 2 or n % 2 == 0:
        return n == 2

    d, r = n - 1, 0
    while d % 2 == 0:               # n - 1 = d * 2^r, d odd
        d //= 2
        r += 1

    for _ in range(rounds):
        a = random.randrange(2, n - 1)
        x = pow(a, d, n)
        if x == 1 or x == n - 1:
            continue
        for _ in range(r - 1):
            x = pow(x, 2, n)
            if x == n - 1:
                break
        else:
            return False            # a proves n composite
    return True


def generate_prime(bits):
    while True:
        p = random.getrandbits(bits) | (1 << (bits - 1)) | 1     # odd, exact size
        if is_prime(p):
            return p


def generate_key(bits=2048, e=65537):
    while True:
        p = generate_prime(bits // 2)
        q = generate_prime(bits // 2)
        phi = (p - 1) * (q - 1)
        if p != q and gcd_ext(e, phi)[0] == 1:
            break

    n = p * q
    d = mod_inverse(e, phi)                     # d = e^-1 (mod phi)
    return {"n": n, "e": e}, {"n": n, "d": d}


# --- data conversion --------------------------------------------------------

def i2osp(x, length):
    ''' integer -> big-endian octet string of exactly `length` bytes '''
    return x.to_bytes(length, "big")


def os2ip(octets):
    ''' octet string -> integer '''
    return int.from_bytes(octets, "big")


def xor_bytes(a, b):
    return bytes(x ^ y for x, y in zip(a, b))


# --- MGF1 mask generation function ------------------------------------------

def mgf1(seed, length):
    ''' Hash(seed||0) || Hash(seed||1) || ... truncated to `length` bytes. '''
    T = b""
    counter = 0
    while len(T) < length:
        T += sha256(seed + i2osp(counter, 4))
        counter += 1
    return T[:length]


# --- EMSA-PSS encoding ------------------------------------------------------

def emsa_pss_encode(M, em_bits):
    ''' EM = maskedDB || H || 0xbc '''
    em_len = (em_bits + 7) // 8
    if em_len < H_LEN + S_LEN + 2:
        raise ValueError("encoding error")

    m_hash = sha256(M)
    salt = os.urandom(S_LEN)                        # fresh salt every signature
    H = sha256(b"\x00" * 8 + m_hash + salt)         # H = Hash(M')

    DB = b"\x00" * (em_len - S_LEN - H_LEN - 2) + b"\x01" + salt
    masked_db = xor_bytes(DB, mgf1(H, em_len - H_LEN - 1))

    spare = 8 * em_len - em_bits                    # clear leftmost bits so EM < n
    masked_db = bytes([masked_db[0] & (0xFF >> spare)]) + masked_db[1:]

    return masked_db + H + b"\xbc"


# --- EMSA-PSS verification --------------------------------------------------

def emsa_pss_verify(M, EM, em_bits):
    em_len = (em_bits + 7) // 8
    if em_len < H_LEN + S_LEN + 2 or len(EM) != em_len:
        return False
    if EM[-1] != 0xBC:                              # trailer field
        return False

    masked_db = EM[: em_len - H_LEN - 1]
    H = EM[em_len - H_LEN - 1: em_len - 1]

    spare = 8 * em_len - em_bits
    if masked_db[0] >> (8 - spare) != 0:            # bits cleared while encoding
        return False

    DB = xor_bytes(masked_db, mgf1(H, em_len - H_LEN - 1))
    DB = bytes([DB[0] & (0xFF >> spare)]) + DB[1:]

    ps_len = em_len - H_LEN - S_LEN - 2             # DB = 0x00...00 || 0x01 || salt
    if DB[:ps_len] != b"\x00" * ps_len or DB[ps_len] != 0x01:
        return False

    salt = DB[ps_len + 1:]                          # recover the salt
    return sha256(b"\x00" * 8 + sha256(M) + salt) == H


# --- RSASSA-PSS sign / verify -----------------------------------------------

def sign(private, M):
    mod_bits = private["n"].bit_length()
    EM = emsa_pss_encode(M, mod_bits - 1)
    s = pow(os2ip(EM), private["d"], private["n"])           # RSASP1
    return i2osp(s, (mod_bits + 7) // 8)


def verify(public, M, signature):
    mod_bits = public["n"].bit_length()
    if len(signature) != (mod_bits + 7) // 8:
        return False

    em_bits = mod_bits - 1
    m = pow(os2ip(signature), public["e"], public["n"])      # RSAVP1
    try:
        EM = i2osp(m, (em_bits + 7) // 8)
    except OverflowError:
        return False
    return emsa_pss_verify(M, EM, em_bits)


public, private = generate_key()
print("n:", public["n"])
print("e:", public["e"])
print("d:", private["d"])

message = input("\nEnter a message to sign: ").encode()
signature = sign(private, message)

print("Signature:", signature.hex())
print("Verified :", verify(public, message, signature))

tampered = message + b"!"
print("\nModified message:", tampered.decode())
print("Verified :", verify(public, tampered, signature))
