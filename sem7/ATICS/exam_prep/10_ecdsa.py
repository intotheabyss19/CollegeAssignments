"""
=====================================================================
 10. Elliptic Curve Digital Signature Algorithm (ECDSA)
=====================================================================

>> ECDSA kya hai? (Purpose)
   - DIGITAL SIGNATURE scheme, elliptic curves pe. Kaam:
       1. AUTHENTICATION  -> message sach mein Alice ne bheja
       2. INTEGRITY       -> message raste mein badla nahi gaya
       3. NON-REPUDIATION -> Alice baad mein mukar nahi sakti
   - Alice PRIVATE key se SIGN karti hai, koi bhi uski PUBLIC key se VERIFY
     kar sakta hai. (Encryption ka ulta: wahan public se lock, private se unlock)
   - DSA ka ECC version. Exp 4 (RSA-PSS) jaisa kaam, lekin chhoti keys.

>> Security kis cheez pe tiki hai?
   - ECDLP: public key Q = d*G se private key d nikalna mushkil hai.
   - Hash function (SHA-256) collision resistant hai.

>> Algorithm
   PUBLIC: curve (p, a, b), base point G, order n (PRIME)
   KEYGEN:  d = random in [1, n-1]  (private),   Q = d*G  (public)

   SIGN(m, d):
     1. e = HASH(m) mod n
     2. k = random in [1, n-1]          (har signature ke liye NAYA k - nonce)
     3. r = (k*G).x mod n               (agar r = 0 -> naya k)
     4. s = k^(-1) * (e + d*r) mod n    (agar s = 0 -> naya k)
     5. signature = (r, s)

   VERIFY(m, (r, s), Q):
     1. check 1 <= r, s <= n-1
     2. e = HASH(m) mod n
     3. w  = s^(-1) mod n
     4. u1 = e*w mod n,   u2 = r*w mod n
     5. X  = u1*G + u2*Q
     6. valid agar X ≠ O aur X.x mod n == r

>> Haath se chhota example (Exp 8 curve: y^2=x^3+2x+2 mod 17, G=(5,1), n=19)
   d = 7  -> Q = 7G = (0, 6)
   Maan lo e = HASH(m) mod 19 = 10,  k = 3
   SIGN:   kG = 3G = (10, 6) -> r = 10 mod 19 = 10
           k^(-1) mod 19 = 13   (3*13 = 39 = 2*19 + 1)
           s = 13 * (10 + 7*10) mod 19 = 13 * 80 mod 19 = 13 * 4 = 52 mod 19 = 14
           signature = (10, 14)
   VERIFY: w  = 14^(-1) mod 19 = 15   (14*15 = 210 = 11*19 + 1)
           u1 = 10*15 mod 19 = 150 mod 19 = 17
           u2 = 10*15 mod 19 = 17
           X  = 17G + 17Q = 17G + 17*7G = (17 + 119)G = 136G = 136 mod 19 = 3G = (10, 6)
           X.x = 10 = r  ✓  VALID

>> Kyun kaam karta hai? (intuition)
   X = u1*G + u2*Q = (e*w)G + (r*w)(d*G) = w*(e + r*d) * G
   s = k^(-1)(e + d*r)  ->  w = s^(-1) = k * (e + d*r)^(-1)
   X = k * (e + d*r)^(-1) * (e + r*d) * G = k*G
   Toh X.x = (kG).x = r  -> match. Message badla -> e badla -> X badla -> fail.

>> Kahan use hota hai?
   - Bitcoin & Ethereum transactions (secp256k1 curve)
   - TLS/HTTPS certificates, SSH keys (ecdsa-sha2-nistp256)
   - Code signing, Apple/Android app signing, e-passports

>> Exam trick (yaad rakhne ke liye)
   SIGN:   "r = (kG).x,   s = k⁻¹(H + d·r)"
   VERIFY: "w = s⁻¹,  u1 = H·w,  u2 = r·w,  X = u1G + u2Q,  X.x == r?"
   Saare mod n mein (p mein nahi!) - sirf point add/mul mein mod p.

>> Viva Questions
   Q1. Digital signature kya provide karta hai?
       Ans: Authentication, integrity, non-repudiation. (Confidentiality NAHI.)
   Q2. Sign kis key se, verify kis key se?
       Ans: Sign = private key d, verify = public key Q = dG.
   Q3. k (nonce) kyun random aur unique hona chahiye?
       Ans: Agar same k do messages pe use ho gaya, toh
            k = (e1 - e2) / (s1 - s2) mod n,  phir d = (s*k - e) / r mod n
            -> private key leak! Sony PS3 hack (2010) yahi galti thi -
            unhone har signature mein same k use kiya.
   Q4. n prime kyun hona chahiye?
       Ans: k^(-1) aur s^(-1) mod n nikalne hain - har non-zero number ka
            inverse tabhi guaranteed hai jab n prime ho.
   Q5. Message ko pehle hash kyun karte hain?
       Ans: Message kitna bhi bada ho, hash fixed size (256-bit) ho jata hai.
            Aur hash tamper detection mein help karta hai.
   Q6. ECDSA vs RSA signature?
       Ans: ECDSA chhoti keys (256-bit vs 3072-bit) aur chhote signatures.
            RSA verification fast hota hai, ECDSA signing fast.
   Q7. ECDSA deterministic hai ya probabilistic?
       Ans: Probabilistic - random k ki wajah se same message ke alag
            signatures aate hain. (RFC 6979 deterministic k banata hai
            hash se, taaki random number generator ki galti na ho.)
   Q8. r = 0 ya s = 0 aaye toh?
       Ans: Naya k choose karke dobara sign karo.
   Q9. Bitcoin kaunsa curve use karta hai?
       Ans: secp256k1: y² = x³ + 7.
   Q10. Tampered message pe verify fail kyun hota hai?
       Ans: Hash e badal jata hai -> u1 badal jata hai -> X ≠ kG -> X.x ≠ r.
"""


# =====================================================================
# PART 1: CODE SAMJHO (Part 2 wala code + har line ka manual)
# =====================================================================
# Neeche bilkul wahi code hai jo PART 2 mein hai, bas har line ke saath
# explanation. Sirf ek farak: input() ki jagah fixed value di hai (taaki
# file chalane pe do baar input na maange). Asli input() line comment mein hai.
print("===== PART 1: Annotated version =====")

# random  -> Python ka built-in module, random numbers ke liye.
#   random.randint(a, b) -> a aur b ke beech ek random integer, DONO ends included.
#     randint(1, 5) -> 1, 2, 3, 4 ya 5 mein se koi bhi.
# hashlib -> built-in module, hash functions deta hai (SHA-256, SHA-1, MD5, ...).
#   hashlib.sha256(data) -> SHA-256 hash object. data BYTES hona chahiye, string nahi.
#     .hexdigest() -> hash as hex STRING (64 characters), e.g. '185f8db3...'
#     .digest()    -> hash as raw BYTES (32 bytes). Yahan hexdigest chahiye,
#                     kyunki usko int(..., 16) se seedha number bana sakte hain.
import random, hashlib

# Curve: y^2 = x^3 + a*x + b (mod p). Tuple unpacking -> p=10007, a=2, b=30
p, a, b = 10007, 2, 30
G = (1, 283)       # base point (generator), sabko pata hota hai. Tuple (x, y)
n = 10091          # order of G: n*G = O (point at infinity). n PRIME hai -> har
                   # non-zero number ka inverse mod n milega (k^-1, s^-1 ke liye zaroori)


# --- ECC point addition (detail Exp 8 mein) ---------------------------
# Point ko tuple (x, y) se represent kiya, aur point at infinity O ko None se.
def add(P, Q):
    if P is None:                      # O + Q = Q   (O identity element hai, jaise 0)
        return Q
    if Q is None:                      # P + O = P
        return P
    x1, y1 = P                         # tuple khol ke x, y nikale
    x2, y2 = Q
    if x1 == x2 and (y1 + y2) % p == 0:    # P + (-P) = O (vertical line)
        return None
    if P == Q:                         # doubling: tangent slope = (3x^2 + a) / (2y)
        top = 3 * x1 * x1 + a
        bottom = 2 * y1
    else:                              # addition: chord slope = (y2 - y1) / (x2 - x1)
        top = y2 - y1
        bottom = x2 - x1
    # Division mod p = inverse se multiply:
    #   pow(x, -1, p) -> x ka modular inverse mod p (Python 3.8+), yaani 1/x mod p
    slope = top * pow(bottom, -1, p) % p
    x3 = (slope * slope - x1 - x2) % p     # x3 = slope^2 - x1 - x2
    y3 = (slope * (x1 - x3) - y1) % p      # y3 = slope(x1 - x3) - y1
    return (x3, y3)


# --- Scalar multiplication k*P (double-and-add, detail Exp 8 mein) ----
# k ke binary bits right se left padho: bit 1 (k odd) ho toh result mein P add karo,
# har step pe P ko double karo. O(log k) steps, k baar add nahi karna padta.
def mul(k, P):
    result = None                      # result shuru mein O (identity)
    while k > 0:                       # jab tak k ke bits bache hain
        if k % 2 == 1:                 # k odd -> last bit 1
            result = add(result, P)
        P = add(P, P)                  # P, 2P, 4P, 8P ...
        k = k // 2                     # last bit hata do
    return result


# --- Hash: message -> number mod n -------------------------------------
# m.encode()               -> string ko bytes mein (UTF-8). "Hi".encode() = b'Hi'
# sha256(...).hexdigest()  -> 64-char hex string
# int(hex_string, 16)      -> int(s, base): string ko given base mein number banao.
#                             int('ff', 16) = 255. Yahan 256-bit ka bada number aata hai.
# % n                      -> usko 0..n-1 range mein laao (ECDSA mein hash mod n chahiye)
def H(m):
    hex_digest = hashlib.sha256(m.encode()).hexdigest()   # message bytes ka SHA-256, hex string
    return int(hex_digest, 16) % n                         # hex -> number, phir mod n


# --- SIGN (private key d se) ----------------------------------------------
# Signature = do numbers (r, s).
def sign(m, d):
    while True:                        # loop sirf edge case ke liye (r ya s = 0 aaye toh retry)
        k = random.randint(1, n - 1)   # nonce k: har signature ke liye NAYA random (secret!)
        point = mul(k, G)              # random point k*G
        r = point[0] % n               # r = (k*G).x mod n   -> [0] se point ka x liya
        # s = k^-1 * (H(m) + d*r) mod n
        #   pow(k, -1, n) -> k ka inverse mod n (n prime hai isliye hamesha milta hai)
        s = pow(k, -1, n) * (H(m) + d * r) % n
        if r != 0 and s != 0:          # r = 0 ya s = 0 wala signature invalid hota hai
            return r, s                # do values return -> tuple (r, s)


# --- VERIFY (public key Q se) -------------------------------------------
# Idea: s = k^-1 (H + d*r)  ->  k = s^-1 (H + d*r) = w*H + w*r*d  (w = s^-1)
#   toh k*G = (w*H)*G + (w*r)*(d*G) = u1*G + u2*Q
#   Verifier ko d nahi pata, lekin Q = d*G pata hai -> wahi point X bana leta hai.
#   Agar X.x mod n == r  -> signature sahi.
def verify(m, r, s, Q):
    if not (0 < r < n and 0 < s < n):  # edge case: range ke bahar -> seedha reject
        return False
    w = pow(s, -1, n)                  # w = s^-1 mod n
    u1 = H(m) * w % n                  # u1 = H(m) * w mod n
    u2 = r * w % n                     # u2 = r * w mod n
    X = add(mul(u1, G), mul(u2, Q))    # X = u1*G + u2*Q  (sahi signature pe X = k*G)
    if X is None:                      # X = O aaye toh reject
        return False
    return X[0] % n == r               # X ka x mod n == r -> valid


# --- Key generation ---------------------------------------------------
d = random.randint(1, n - 1)           # private key d: random number in [1, n-1]
Q = mul(d, G)                          # public key Q = d*G (point). Q se d nikalna = ECDLP (hard)
print("Private key d:", d, " Public key Q:", Q)

# message = input("Enter a message to sign: ")
message = "Hello Bob"
r, s = sign(message, d)                # tuple return ko seedha r, s mein unpack kiya
print("Signature (r, s):", (r, s))
print("Verified:", verify(message, r, s, Q))        # True

# Message mein ek character badla -> hash badla -> u1 badla -> X.x != r -> False
tampered = message + "!"
print("\nModified message:", tampered)
print("Verified:", verify(tampered, r, s, Q))       # False


# =====================================================================
# PART 2: EXAM VERSION (bina comments - yahi likhna hai / ratna hai)
# =====================================================================
print("\n===== PART 2: Exam version =====")

import random, hashlib

p, a, b = 10007, 2, 30
G = (1, 283)
n = 10091


def add(P, Q):
    if P is None:
        return Q
    if Q is None:
        return P
    x1, y1 = P
    x2, y2 = Q
    if x1 == x2 and (y1 + y2) % p == 0:
        return None
    if P == Q:
        top = 3 * x1 * x1 + a
        bottom = 2 * y1
    else:
        top = y2 - y1
        bottom = x2 - x1
    slope = top * pow(bottom, -1, p) % p
    x3 = (slope * slope - x1 - x2) % p
    y3 = (slope * (x1 - x3) - y1) % p
    return (x3, y3)


def mul(k, P):
    result = None
    while k > 0:
        if k % 2 == 1:
            result = add(result, P)
        P = add(P, P)
        k = k // 2
    return result


def H(m):
    hex_digest = hashlib.sha256(m.encode()).hexdigest()
    return int(hex_digest, 16) % n


def sign(m, d):
    while True:
        k = random.randint(1, n - 1)
        point = mul(k, G)
        r = point[0] % n
        s = pow(k, -1, n) * (H(m) + d * r) % n
        if r != 0 and s != 0:
            return r, s


def verify(m, r, s, Q):
    if not (0 < r < n and 0 < s < n):
        return False
    w = pow(s, -1, n)
    u1 = H(m) * w % n
    u2 = r * w % n
    X = add(mul(u1, G), mul(u2, Q))
    if X is None:
        return False
    return X[0] % n == r


d = random.randint(1, n - 1)
Q = mul(d, G)
print("Private key d:", d, " Public key Q:", Q)

message = input("Enter a message to sign: ")
r, s = sign(message, d)
print("Signature (r, s):", (r, s))
print("Verified:", verify(message, r, s, Q))

tampered = message + "!"
print("\nModified message:", tampered)
print("Verified:", verify(tampered, r, s, Q))
