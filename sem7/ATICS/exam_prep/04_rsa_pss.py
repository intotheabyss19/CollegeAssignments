"""
=====================================================================
 4. Digital Signature using RSA-PSS (Probabilistic Signature Scheme)
    Generate + verify signature, aur modified message ka REJECTION dikhao
    (FROM SCRATCH - sirf hashlib, os, random, math helpers use kiye hain)
=====================================================================

>> Lab exam rule (sir ne bola)
   Library sirf HELPER ke liye: hashlib (SHA-256), os.urandom / random (randomness),
   math.gcd, pow, sympy.randprime (primes). Lekin "direct" function jo poora PSS
   kar de (cryptography ka private_key.sign(..., padding.PSS ...)) - NOT allowed.
   Isliye RSA keygen + MGF1 + PSS encode/verify sab khud likha hai.

>> Digital signature kya hai? (Purpose)
   - Encryption = secrecy (koi padh na sake).
     Signature   = AUTHENTICATION + INTEGRITY + NON-REPUDIATION:
       Authentication  : message sach mein Alice ne bheja
       Integrity       : raaste mein 1 bit bhi nahi badla
       Non-repudiation : Alice baad mein mukar nahi sakti ki "maine nahi bheja"
   - RSA ulta use hota hai:
       SIGN   = PRIVATE key se  (sirf Alice kar sakti hai)   s = EM^d mod n
       VERIFY = PUBLIC key se   (koi bhi check kar sakta hai) EM = s^e mod n

>> Textbook RSA signature (base idea, Exp 3 wala RSA) + haath se example
     sign   : s = H(m)^d mod n
     verify : s^e mod n == H(m) ?
   Example (Exp 3 ki keys): n = 3233, e = 17, d = 2753, maan lo H(m) = 65
     s = 65^2753 mod 3233 = 588
     verify: 588^17 mod 3233 = 65  == H(m)  ✓
   Problem: deterministic hai (same message -> same signature) aur
   mathematical structure ki wajah se forgery attacks possible hain.
   -> Solution: hash ko seedha sign mat karo, pehle PSS se "encode" karo.

>> RSA KEY GENERATION (khud se)
   1. 512-bit random ODD number lo, top 2 bits 1 karo (taaki n poora 1024-bit bane)
   2. Miller-Rabin test se check karo prime hai ya nahi, nahi toh dobara try
   3. p, q mil gaye -> n = p*q, phi = (p-1)(q-1), e = 65537, d = e^(-1) mod phi
      d = pow(e, -1, phi)   (ya Exp 3 wala gcd_ext - dono chalega)
   EXAM VERSION (PART 2) mein shortcut use kiya hai (allowed helper):
     from sympy import randprime;  p = randprime(3 * 2**510, 2**512)   (pip install sympy)
     (3 * 2**510 se start -> top 2 bits 1 -> n pakka 1024-bit)
   Miller-Rabin sirf samajhne ke liye PART 1 mein hai (agar sympy na ho toh backup).

   MILLER-RABIN (prime test):
     n - 1 = d * 2^r  (d odd) likho
     random a lo, x = a^d mod n
     agar x == 1 ya x == n-1 -> is round mein pass
     warna x ko r-1 baar square karo; kabhi n-1 aaya -> pass, kabhi nahi -> COMPOSITE
     20 rounds pass -> almost surely PRIME (galti ka chance < 4^-20)

>> PSS ENCODE + SIGN (sizes 1024-bit n ke liye: K = 128 bytes)
     1. mHash = SHA256(message)                         32 bytes
     2. salt  = os.urandom(32)  (har signature mein naya) 32 bytes
     3. M'    = 8 zero bytes || mHash || salt           72 bytes
     4. H     = SHA256(M')                              32 bytes
     5. DB    = PS (62 zero bytes) || 0x01 || salt      95 bytes  (= K - 32 - 1)
     6. maskedDB = DB XOR MGF1(H, 95)
     7. maskedDB ka sabse left wala 1 bit 0 karo  (taaki EM < n rahe)
     8. EM    = maskedDB || H || 0xBC                  128 bytes
     9. signature s = EM^d mod n                         (normal RSA private op)

   MGF1(seed, len) = SHA256(seed||0) || SHA256(seed||1) || ...  pehle len bytes
     (counter 4 bytes ka hota hai) -> hash ko "lamba" banane ki machine.

>> PSS VERIFY
     1. EM = s^e mod n  (128 bytes mein convert)
     2. last byte 0xBC hai? maskedDB ka top bit 0 hai?  nahi -> INVALID
     3. maskedDB = EM[:95],  H = EM[95:127]
     4. DB = maskedDB XOR MGF1(H, 95), top bit 0 karo
     5. DB = 62 zeros || 0x01 || salt  format check karo, salt = last 32 bytes
     6. H' = SHA256(8 zeros || SHA256(message) || salt)
     7. H' == H -> VALID, warna INVALID

>> Kyun kaam karta hai?
   - s^e = (EM^d)^e = EM mod n  (Exp 3 wala RSA logic) -> Bob ko Alice ka EM wapas milta hai.
   - Salt DB ke andar chhupa (mask) hai, Bob MGF1(H) se XOR karke salt nikaal leta hai,
     phir khud H' banake compare karta hai.
   - Sirf private key d wala hi aisa s bana sakta hai jiska s^e sahi EM de.
   - Message 1 character bhi badla -> SHA256 poora badal jaata hai (avalanche effect)
     -> H' != H -> REJECT.
   - Random salt -> same message ke do signatures ALAG, phir bhi dono valid.

>> Kahan use hota hai?
   - TLS 1.3 handshake mein RSA signatures ke liye PSS mandatory.
   - Code signing, software updates, PDF/e-documents, Aadhaar eSign jaisi cheezein.
   - Purana scheme: PKCS#1 v1.5 (deterministic). Naya recommended: PSS (RFC 8017).

>> Exam trick (yaad rakhne ke liye)
   Keygen  : "randprime randprime -> n phi -> d = pow(e, -1, phi)"
   Encode  : "8 zero | mHash | salt -> H ;  zeros 01 salt -> DB ;  DB xor MGF(H) ;
              top bit 0 ;  masked | H | BC"
   Numbers : K = 128, H aur salt = 32, DB = K-33 = 95, zeros = K-66 = 62
   Verify  : bilkul ulta - EM todo, unmask, salt nikalo, H dobara banao, compare.

>> Viva Questions
   Q1. Signing kis key se aur verification kis key se?
       Ans: Sign = sender ki private key. Verify = sender ki public key.
   Q2. Digital signature kya guarantee deta hai?
       Ans: Authentication, integrity, non-repudiation. (Confidentiality NAHI.)
   Q3. PSS ka full form? Kis standard mein hai?
       Ans: Probabilistic Signature Scheme. PKCS#1 v2.x / RFC 8017.
   Q4. "Probabilistic" kyun?
       Ans: Har baar random salt use hota hai, toh same message ke signatures alag aate hain.
   Q5. MGF1 kya hai?
       Ans: Mask Generation Function - SHA-256 ko counter (0,1,2..) ke saath baar baar
            chala ke kisi bhi length ka mask banata hai.
   Q6. 0xBC aur 8 zero bytes kyun?
       Ans: 0xBC fixed "trailer" byte hai (format check). 8 zero bytes M' ka fixed
            prefix hai - standard ne define kiya hai.
   Q7. maskedDB ka leftmost bit 0 kyun karte hain?
       Ans: Taaki EM (as number) n se chhota rahe, warna EM^d mod n se wapas EM nahi milega.
   Q8. Pura message sign kyun nahi karte, hash kyun?
       Ans: Message bada ho sakta hai (n se bada). Hash fixed size (32 bytes) aur fast.
   Q9. Miller-Rabin kya hai, deterministic hai?
       Ans: Probabilistic primality test. Composite ko har round 3/4 chance se pakadta
            hai, 20 rounds ke baad galti ka chance negligible.
   Q10. PKCS#1 v1.5 vs PSS?
       Ans: v1.5 deterministic aur purana. PSS randomized aur provably secure.
   Q11. Signature ka size kitna hota hai?
       Ans: n ke barabar. 1024-bit n -> 128 bytes, 2048-bit -> 256 bytes.
   Q12. Encryption aur signature mein keys ka fark?
       Ans: Encryption: public se encrypt, private se decrypt.
            Signature : private se sign, public se verify. (Bilkul ulta.)
"""


# =====================================================================
# PART 1: CODE SAMJHO (Part 2 wala code + har line ka manual)
# =====================================================================
# Neeche bilkul wahi code hai jo PART 2 mein hai, bas har line ke saath
# explanation. Sirf ek farak: input() ki jagah fixed value di hai (taaki
# file chalane pe do baar input na maange). Asli input() line comment mein hai.
# Ek aur farak: sympy na ho toh yahan apna Miller-Rabin backup chalta hai.
print("===== PART 1: Annotated version =====")

# --- Imports ----------------------------------------------------------
# hashlib -> Python ka built-in module, hash functions deta hai (sha256, md5...).
#   hashlib.sha256(data) : data BYTES hona chahiye (string nahi). Hash object deta hai.
#     .digest()    -> 32 raw bytes, jaise b'\x9f\x86...'   (yahan yahi chahiye)
#     .hexdigest() -> same cheez 64-char hex STRING mein, jaise '9f86d0...'
# os -> operating system wala module. Hum sirf os.urandom(n) use karte hain:
#   os.urandom(n) -> n cryptographically secure random BYTES. os.urandom(32) = 32-byte salt.
#   (random module ka random crypto ke liye safe nahi hota, isliye salt ke liye os.urandom)
import hashlib, os

# sympy -> maths library (pip install sympy). Sirf ek HELPER chahiye:
#   randprime(a, b) -> range [a, b) mein ek random PRIME number (a included, b nahi).
#   randprime(3 * 2**510, 2**512) -> 512-bit prime jiske top 2 bits 1 hain.
#   Kyun 3 * 2**510? Toh p, q dono >= 1.5 * 2^511 -> p*q >= 2.25 * 2^1022 > 2^1023
#   -> n pakka 1024-bit (128 bytes) banta hai. Neeche K = 128 isi pe depend karta hai.
try:
    from sympy import randprime
except ImportError:
    # --- BACKUP: sympy na ho toh apna Miller-Rabin (exam mein bhi likh sakte ho) ---
    import random

    def is_prime(n, rounds=20):
        if n < 2 or n % 2 == 0:              # 0, 1, even numbers (2 ko chhod ke) prime nahi
            return n == 2
        d, r = n - 1, 0
        while d % 2 == 0:                    # n - 1 = d * 2^r likho, d odd
            d, r = d // 2, r + 1
        for _ in range(rounds):              # har round mein ek random "witness" a
            x = pow(random.randrange(2, n - 1), d, n)   # x = a^d mod n
            if x in (1, n - 1):              # yeh prime jaisa behave kar raha, agla round
                continue
            for _ in range(r - 1):           # x ko baar baar square karo
                x = pow(x, 2, n)
                if x == n - 1:
                    break                    # n-1 mil gaya -> pass
            else:                            # loop bina break ke khatam -> pakka COMPOSITE
                return False
        return True                          # sab rounds pass -> almost surely prime

    def randprime(a, b):                     # sympy jaisa hi: [a, b) mein random prime
        while True:
            p = random.randrange(a, b) | 1   # random number, "| 1" se odd bana do
            if is_prime(p):
                return p

# K = EM (encoded message) ki length bytes mein = n ki length = 1024 bits / 8 = 128.
K = 128


# H(b) -> SHA-256 hash, 32 bytes return. Chhota naam isliye ki baar baar use hoga.
def H(b):
    return hashlib.sha256(b).digest()


# MGF1 = Mask Generation Function: chhote seed se KITNE BHI bytes ka "mask" banata hai.
#   Idea: seed + counter (0, 1, 2, ...) ko hash karte jao aur output mein jodte jao,
#   jab tak output kam se kam `length` bytes ka na ho jaaye. Har hash 32 bytes deta hai.
def mgf1(seed, length):
    output = b''                             # b'' = khaali bytes object (string ka bytes version)
    counter = 0
    while len(output) < length:              # jab tak abhi bhi bytes kam hain
        # counter.to_bytes(4, 'big') -> integer ko exactly 4 bytes mein likho,
        #   'big' = bada byte pehle (big-endian). Jaise 1 -> b'\x00\x00\x00\x01'
        output += H(seed + counter.to_bytes(4, 'big'))   # bytes + bytes = jod do
        counter += 1
    return output[:length]                   # [:length] -> extra bytes kaat do, exactly length bytes


# Do byte-strings ka byte-by-byte XOR (dono same length ke hone chahiye).
def xor(a, b):
    result = b''
    for i in range(len(a)):
        # a[i] -> bytes object pe indexing ek INT (0-255) deta hai, jaise b'AB'[0] = 65
        # ^     -> bitwise XOR of two ints: 1 jahan bits alag, 0 jahan same
        # bytes([x]) -> ek int ki list se 1-byte bytes object banata hai: bytes([65]) = b'A'
        result += bytes([a[i] ^ b[i]])
    return result


# RSA keys banao. e=65537 default argument (sabse common public exponent).
def keygen(e=65537):
    while True:                              # jab tak achhi key na mile, retry
        p = randprime(3 * 2**510, 2**512)    # 512-bit prime
        q = randprime(3 * 2**510, 2**512)    # doosra 512-bit prime
        phi = (p - 1) * (q - 1)
        # Edge cases: p == q nahi hona chahiye; e ka inverse tabhi exist karta hai
        # jab gcd(e, phi) = 1. e prime hai, toh bas check karo phi e se divisible na ho.
        if p != q and phi % e != 0:
            # pow(e, -1, phi) -> e ka modular inverse = d (Python 3.8+ built-in)
            d = pow(e, -1, phi)
            n = p * q
            return e, d, n


# SIGN = EMSA-PSS-ENCODE + RSA private key operation.
#   Layout yaad rakho (K = 128 bytes):
#   DB = [ PS: 62 zero bytes (K-66) | 0x01 | salt (32 bytes) ]          -> 95 bytes (K-33)
#   EM = [ maskedDB (95 bytes) | h (32 bytes) | 0xbc (1 byte) ]         -> 128 bytes (K)
def sign(m, d, n):
    salt = os.urandom(32)                    # har baar naya random salt -> PROBABILISTIC
    m_hash = H(m)                            # message ka hash (32 bytes)
    # bytes(8) -> 8 zero bytes b'\x00' * 8. Standard (RFC 8017) yahi bolta hai:
    # M' = 8 zeros || mHash || salt  ->  h = H(M')
    m_dash = bytes(8) + m_hash + salt
    h = H(m_dash)
    ps = bytes(K - 66)                       # padding string: 62 zero bytes
    db = ps + b'\x01' + salt                 # 0x01 = separator, padding kahan khatam hai batata hai
    masked_db = xor(db, mgf1(h, K - 33))     # DB ko MGF1(h) se mask karo -> salt chhup jaata hai
    # Pehle byte ka top bit 0 karo: & 0x7F (0x7F = 0111 1111, top bit hat jaata hai).
    #   Taaki EM ka integer n se chhota rahe (warna mod n mein info kho jaayegi).
    #   masked_db[0] -> pehla byte as INT, bytes([...]) se wapas 1-byte bytes banaya.
    first_byte = masked_db[0] & 0x7F
    masked_db = bytes([first_byte]) + masked_db[1:]      # [1:] = pehle byte ke baad sab
    em = masked_db + h + b'\xbc'             # 0xbc = fixed trailer byte (last byte)
    # int.from_bytes(em, 'big') -> 128 bytes ko ek bada integer bana do (big-endian)
    em_int = int.from_bytes(em, 'big')
    return pow(em_int, d, n)                 # RSA sign: s = EM^d mod n  (PRIVATE key d se)


# VERIFY = RSA public key operation + EMSA-PSS-VERIFY (sign ka bilkul ulta).
def verify(m, s, e, n):
    em_int = pow(s, e, n)                    # s^e mod n = EM wapas (PUBLIC key se)
    # .to_bytes(K, 'big') -> integer ko exactly 128 bytes mein likho (aage zeros pad ho jaate hain)
    em = em_int.to_bytes(K, 'big')
    if em[-1] != 0xbc:                       # em[-1] = last byte. Trailer galat -> reject
        return False
    masked_db = em[:K - 33]                  # pehle 95 bytes
    h = em[K - 33:K - 1]                     # index 95 se 126 tak = 32-byte h (trailer se pehle)
    db = xor(masked_db, mgf1(h, K - 33))     # XOR dobara lagao -> mask hat jaata hai, DB wapas
    if db[K - 66] != 1:                      # 62 zeros ke baad wala byte 0x01 hona chahiye
        return False
    salt = db[-32:]                          # DB ke last 32 bytes = salt
    # Signer ki tarah h dobara banao; match hua -> message wahi hai jo sign hua tha.
    m_dash = bytes(8) + H(m) + salt
    return H(m_dash) == h


# --- Main -------------------------------------------------------------
e, d, n = keygen()
# message = input("Enter a message to sign: ").encode()
#   .encode() -> string ko bytes banata hai (UTF-8), kyunki hash ko bytes chahiye.
message = "Hello Bob".encode()
sig = sign(message, d, n)
# sig ek bahut bada integer hai (~300 digits) - seedha print, lamba dikhega, koi baat nahi
print("Signature:", sig)
print("Verified:", verify(message, sig, e, n))      # True

tampered = message + b"!"                             # message mein ek char badla
# .decode() -> bytes wapas string (sirf print karne ke liye)
print("\nModified message:", tampered.decode())
print("Verified:", verify(tampered, sig, e, n))     # False -> forgery/badlaav pakda gaya


# =====================================================================
# PART 2: EXAM VERSION (bina comments - yahi likhna hai / ratna hai)
# =====================================================================
print("\n===== PART 2: Exam version =====")

import hashlib, os
from sympy import randprime

K = 128


def H(b):
    return hashlib.sha256(b).digest()


def mgf1(seed, length):
    output = b''
    counter = 0
    while len(output) < length:
        output += H(seed + counter.to_bytes(4, 'big'))
        counter += 1
    return output[:length]


def xor(a, b):
    result = b''
    for i in range(len(a)):
        result += bytes([a[i] ^ b[i]])
    return result


def keygen(e=65537):
    while True:
        p = randprime(3 * 2**510, 2**512)
        q = randprime(3 * 2**510, 2**512)
        phi = (p - 1) * (q - 1)
        if p != q and phi % e != 0:
            d = pow(e, -1, phi)
            n = p * q
            return e, d, n


def sign(m, d, n):
    salt = os.urandom(32)
    m_hash = H(m)
    m_dash = bytes(8) + m_hash + salt
    h = H(m_dash)
    ps = bytes(K - 66)
    db = ps + b'\x01' + salt
    masked_db = xor(db, mgf1(h, K - 33))
    first_byte = masked_db[0] & 0x7F
    masked_db = bytes([first_byte]) + masked_db[1:]
    em = masked_db + h + b'\xbc'
    em_int = int.from_bytes(em, 'big')
    return pow(em_int, d, n)


def verify(m, s, e, n):
    em_int = pow(s, e, n)
    em = em_int.to_bytes(K, 'big')
    if em[-1] != 0xbc:
        return False
    masked_db = em[:K - 33]
    h = em[K - 33:K - 1]
    db = xor(masked_db, mgf1(h, K - 33))
    if db[K - 66] != 1:
        return False
    salt = db[-32:]
    m_dash = bytes(8) + H(m) + salt
    return H(m_dash) == h


e, d, n = keygen()
message = input("Enter a message to sign: ").encode()
sig = sign(message, d, n)
print("Signature:", sig)
print("Verified:", verify(message, sig, e, n))

tampered = message + b"!"
print("\nModified message:", tampered.decode())
print("Verified:", verify(tampered, sig, e, n))
