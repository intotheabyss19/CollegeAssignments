# 4. Generate and verify a digital signature and demonstrate rejection of a
#    modified message using RSA-PSS (Probabilistic Signature Scheme).
#
# Uses the three packages recommended by the lab manual:
#   sympy        -> build the RSA key material by hand (p, q, n, phi, e, d)
#   cryptography -> the actual RSA-PSS signing / verification (EMSA-PSS + MGF1)
#   ecdsa        -> a side-by-side comparison with an elliptic-curve scheme

from sympy import randprime, gcd, mod_inverse

from cryptography.exceptions import InvalidSignature
from cryptography.hazmat.primitives import hashes
from cryptography.hazmat.primitives.asymmetric import padding, rsa

from ecdsa import BadSignatureError, NIST256p, SigningKey


# key material
def rsa_keypair(bits=1024, e=65537):
    ''' Pick p, q with sympy and hand the numbers to `cryptography`.
        bits is the size of each prime, so the modulus n is 2*bits long. '''
    while True:
        p = randprime(2 ** (bits - 1), 2 ** bits)
        q = randprime(2 ** (bits - 1), 2 ** bits)
        if p == q:
            continue
        phi = (p - 1) * (q - 1)
        if gcd(e, phi) == 1:
            break

    if p < q:                       # cryptography wants iqmp = q^-1 mod p
        p, q = q, p

    n = p * q
    phi = (p - 1) * (q - 1)
    d = mod_inverse(e, phi)         # d = e^-1 (mod phi)

    print(f"p     : {p}")
    print(f"q     : {q}")
    print(f"n     : {n}")
    print(f"phi   : {phi}")
    print(f"e     : {e}")
    print(f"d     : {d}")
    print(f"e*d mod phi = {(e * d) % phi}   (must be 1)\n")

    private_numbers = rsa.RSAPrivateNumbers(
        p=p,
        q=q,
        d=d,
        dmp1=rsa.rsa_crt_dmp1(d, p),
        dmq1=rsa.rsa_crt_dmq1(d, q),
        iqmp=rsa.rsa_crt_iqmp(p, q),
        public_numbers=rsa.RSAPublicNumbers(e=e, n=n),
    )
    return private_numbers.private_key()


# PSS parameters: SHA-256 everywhere, salt as long as the modulus allows
PSS = padding.PSS(
    mgf=padding.MGF1(hashes.SHA256()),
    salt_length=padding.PSS.MAX_LENGTH,
)


class Alice:
    ''' The signer. Holds the private key. '''

    def __init__(self, bits=1024, e=65537):
        self.private_key = rsa_keypair(bits, e)
        self.public = self.private_key.public_key()

    def sign(self, m):
        return self.private_key.sign(m, PSS, hashes.SHA256())


class Bob:
    ''' The verifier. Only ever sees Alice's public key. '''

    def __init__(self, pub):
        self.pub = pub

    def verify(self, m, signature):
        try:
            self.pub.verify(signature, m, PSS, hashes.SHA256())
            return True
        except InvalidSignature:
            return False


A = Alice()
B = Bob(A.public)

message = input("Enter a message to sign: ").encode()

signature = A.sign(message)
print("\nMessage  :", message)
print("Signature:", signature.hex())
print("Verified :", B.verify(message, signature))

# rejection of a modified message
tampered = message + b"!"
print("\nTampered message :", tampered)
print("Verified         :", B.verify(tampered, signature))

# rejection of a modified signature 
bad_sig = bytearray(signature)
bad_sig[0] ^= 0x01                  # flip a single bit
print("\nTampered signature (1 bit flipped)")
print("Verified         :", B.verify(message, bytes(bad_sig)))

# PSS is probabilistic: same message, different signature every time
print("\nSigning the same message twice (random salt each time):")
s1 = A.sign(message)
s2 = A.sign(message)
print("sig1 :", s1.hex()[:64], "...")
print("sig2 :", s2.hex()[:64], "...")
print("equal:", s1 == s2, " both verify:", B.verify(message, s1), B.verify(message, s2))


# comparison: the same demo with ECDSA (experiment 10)
print("\n--- ECDSA over NIST P-256, for comparison ---")
sk = SigningKey.generate(curve=NIST256p)
vk = sk.get_verifying_key()

ec_sig = sk.sign(message)
print("Signature:", ec_sig.hex())


def ec_verify(m, sig):
    try:
        return vk.verify(sig, m)
    except BadSignatureError:
        return False

print("Verified          :", ec_verify(message, ec_sig))
print("Tampered message  :", ec_verify(tampered, ec_sig))
