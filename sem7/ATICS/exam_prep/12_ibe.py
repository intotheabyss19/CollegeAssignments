"""
=====================================================================
 12. Identity-Based Encryption (IBE): Setup, Extract, Encrypt, Decrypt
=====================================================================

>> IBE kya hai? (Purpose)
   - Normal public-key crypto (RSA/ECC) mein public key ek random number hota hai.
     Bob ki public key sahi hai ya nahi - yeh prove karne ke liye CERTIFICATE
     chahiye (PKI, Certificate Authority, certificate revocation... bahut jhanjhat).
   - IBE ka idea (Shamir 1984): Bob ki IDENTITY hi uski PUBLIC KEY hai!
       jaise "bob@nitsikkim.ac.in" -> yahi public key
     Alice ko Bob ka certificate nahi chahiye, sirf uska email chahiye.
   - Pehli practical IBE scheme: Boneh-Franklin (2001), BILINEAR PAIRING se (Exp 11).

>> PKG (Private Key Generator) - trusted authority
   - Ek trusted server jiske paas MASTER SECRET KEY s hoti hai.
   - Wahi har user ki private key banata hai (identity se).
   - Isliye users ko private key ke liye PKG pe trust karna padta hai.

>> Algorithm - 4 steps (Boneh-Franklin, pairing model of Exp 11)
   Notation: G1 = Z_q (generator P), e = pairing,  H1: ID -> G1,  H2: GT -> bytes
   1. SETUP (PKG karta hai, ek baar):
        s = random master secret key
        P_pub = s * P               (master PUBLIC key, sabko de do)
   2. EXTRACT (PKG, har user ke liye):
        Q_ID = H1(ID)               (identity ko hash karke point banao)
        d_ID = s * Q_ID             (user ki PRIVATE key, secretly user ko do)
   3. ENCRYPT (Alice, sirf ID aur P_pub chahiye):
        r = random
        U = r * P
        K = e(Q_ID, P_pub)^r        (shared "mask")
        V = M XOR H2(K)
        Ciphertext = (U, V)
   4. DECRYPT (Bob, apni d_ID se):
        K = e(d_ID, U)
        M = V XOR H2(K)

>> Kyun kaam karta hai? (pairing equation - yeh likhna zaroor)
   Bob ka K  = e(d_ID, U) = e(s*Q_ID, r*P) = e(Q_ID, P)^(s*r)
   Alice ka K = e(Q_ID, P_pub)^r = e(Q_ID, s*P)^r = e(Q_ID, P)^(s*r)
   Dono same! (Bilinearity se s aur r bahar exponent mein aa gaye.)
   Attacker ke paas s nahi, r nahi -> K nahi bana sakta.

>> Problems / limitations
   - KEY ESCROW: PKG ke paas s hai, toh woh KISI BHI user ki private key bana
     sakta hai aur sabke messages padh sakta hai. PKG ko fully trust karna padega.
   - Private key ko secure channel se user tak bhejna padta hai.
   - Revocation mushkil: ID change nahi hoti. Fix: ID mein date jodo,
     jaise "bob@nitsikkim.ac.in || 2026" -> har saal nayi key.
   - Hamara pairing model insecure hai (Exp 11 dekho) - sirf workflow samajhne ke liye.

>> Kahan use hota hai?
   - Email encryption (Voltage SecureMail / HP), enterprise systems jahan ek
     organisation khud PKG ban sakti hai
   - IoT / wireless sensor networks (certificates heavy hote hain)
   - Smart grids, healthcare systems; standard: IEEE 1363.3, RFC 5091

>> Exam trick
   "Setup -> Extract -> Encrypt -> Decrypt"  =  "s,P_pub -> s*H1(ID) -> (rP, M xor H2) -> e(d, U)"
   Sender:  e(H1(ID), P_pub)^r     Receiver: e(d_ID, U)    -> dono barabar.

>> Viva Questions
   Q1. IBE kya hai?
       Ans: Public-key encryption jisme user ki identity (email/phone) hi public key hai.
   Q2. IBE kaunsi problem solve karta hai?
       Ans: Certificates / PKI ki zaroorat khatam - public key authentic hai ya
            nahi check karne ki zaroorat nahi.
   Q3. IBE ka concept kisne diya aur pehli practical scheme kisne?
       Ans: Concept: Adi Shamir (1984). Practical scheme: Boneh-Franklin (2001) using pairings.
   Q4. IBE ke 4 algorithms?
       Ans: Setup, Extract, Encrypt, Decrypt.
   Q5. PKG kya hai?
       Ans: Private Key Generator - trusted authority jiske paas master secret
            key hai aur jo users ki private keys banata hai.
   Q6. Key escrow problem kya hai?
       Ans: PKG kisi bhi user ki private key bana sakta hai, toh sab messages
            decrypt kar sakta hai. Solutions: multiple PKGs (threshold),
            certificateless cryptography.
   Q7. H1 aur H2 ka kaam?
       Ans: H1: identity string -> group element (Q_ID). H2: pairing output ->
            bit string (keystream) jo message ke saath XOR hota hai.
   Q8. Decryption correct kyun hai?
       Ans: e(sQ_ID, rP) = e(Q_ID, sP)^r - bilinearity se.
   Q9. Encryption mein random r kyun?
       Ans: Har baar alag ciphertext aaye (probabilistic encryption), same message
            same ID pe bhi.
   Q10. Kya sender ko receiver ki private key ya certificate chahiye?
       Ans: Nahi - sirf receiver ki ID aur PKG ka public P_pub.
   Q11. Galat ID ki key se decrypt karein toh?
       Ans: e(d_wrong, U) alag K deta hai -> H2 alag -> garbage output.
   Q12. User revoke kaise karein?
       Ans: ID mein expiry/date jodo ("bob@x.com||2026"), naya period = nayi key.
"""


# =====================================================================
# PART 1: CODE SAMJHO (Part 2 wala code + har line ka manual)
# =====================================================================
# Neeche bilkul wahi code hai jo PART 2 mein hai, bas har line ke saath
# explanation. Sirf ek farak: input() ki jagah fixed value di hai (taaki
# file chalane pe do baar input na maange). Asli input() line comment mein hai.
print("===== PART 1: Annotated version =====")

# random  -> built-in module.
#   random.randint(a, b) -> a se b tak random integer, DONO ends included.
# hashlib -> built-in module, hash functions.
#   hashlib.sha256(data).hexdigest() -> SHA-256 hash, 64-char hex STRING. data = bytes.
#   hashlib.shake_256(data).digest(length) -> SHAKE-256 "extendable output" hash:
#       jitni length (bytes) maango utna output deta hai. digest(15) -> 15 bytes.
#       Isliye keystream banane ke liye perfect: message jitna lamba, utni keystream.
import random, hashlib

# Pairing parameters (Exp 11 wale): q, p primes (p = 2q + 1), g = GT generator,
# P = G1 generator. Tuple unpacking.
q, p, g, P = 1019, 2039, 4, 7


# Pairing: e(X, Y) = g^(X*Y mod q) mod p  (detail Exp 11 mein)
# Main property jo IBE use karta hai: e(aX, bY) = e(X, Y)^(ab)
def e(X, Y):
    return pow(g, X * Y % q, p)


# --- H1: identity (string) -> G1 ka point (number 1..q-1) ----------------
# ID.encode()        -> string ko bytes: "bob@x".encode() = b'bob@x'
# int(hex, 16)       -> hex string ko number (base 16)
# % (q - 1) + 1      -> range 1..q-1 mein laao (0 nahi chahiye, 0 se pairing hamesha 1)
def H1(ID):
    return int(hashlib.sha256(ID.encode()).hexdigest(), 16) % (q - 1) + 1


# --- H2: GT element (number) -> keystream bytes ----------------------------
# str(x).encode() -> number ko string, phir bytes: 1014 -> '1014' -> b'1014'
# .digest(length) -> utne bytes ka output
def H2(x, length):
    return hashlib.shake_256(str(x).encode()).digest(length)


# --- XOR do byte strings --------------------------------------------------
# zip(a, b)    -> dono se ek-ek element ka pair deta hai: (a[0], b[0]), (a[1], b[1]) ...
# i ^ j        -> bitwise XOR do bytes (0-255 ke ints) ka
# bytes(list)  -> ints ki list/generator se bytes object banao
# XOR ka magic: (M ^ K) ^ K = M  -> same function encrypt aur decrypt dono karta hai
def xor(a, b):
    return bytes(i ^ j for i, j in zip(a, b))


# --- EXTRACT (PKG karta hai): user ka private key ---------------------------
# Q_ID = H1(ID)  (public, koi bhi bana sakta hai)
# d_ID = s * Q_ID mod q  -> sirf PKG bana sakta hai kyunki master key s sirf usko pata hai
def extract(ID, s):
    return s * H1(ID) % q


# --- ENCRYPT (sender): sirf ID aur P_pub chahiye, koi certificate nahi -------
def encrypt(M, ID, P_pub):
    r = random.randint(1, q - 1)       # har message ke liye fresh random r
    # K = e(Q_ID, P_pub)^r  -> shared secret (GT ka element)
    #   pow(base, exp, mod) -> (base ** exp) % mod, fast
    K = pow(e(H1(ID), P_pub), r, p)
    # Ciphertext = (U, V):
    #   U = r*P        -> receiver ko r ka "hint" (r khud nahi, sirf rP)
    #   V = M XOR H2(K) -> message ko keystream se XOR kiya (len(M) jitni keystream)
    return r * P % q, xor(M, H2(K, len(M)))     # tuple (U, V) return


# --- DECRYPT (receiver): apne private key d_ID se -------------------------
# Receiver K kaise banata hai? e(d_ID, U) = e(s*Q_ID, r*P) = e(Q_ID, P)^(s*r)
#                                         = e(Q_ID, s*P)^r = e(Q_ID, P_pub)^r = K  ✓
# Same K -> same keystream -> XOR karke M wapas.
def decrypt(U, V, d):
    return xor(V, H2(e(d, U), len(V)))


# --- SETUP (PKG karta hai, ek hi baar) ---------------------------------------
s = random.randint(1, q - 1)           # master secret key s (sirf PKG ke paas)
P_pub = s * P % q                      # master public key P_pub = s*P (sabko publish)
print("Setup  : master key s =", s, " P_pub =", P_pub)

# ID = input("Enter receiver's ID: ")
ID = "bob@nitsikkim.ac.in"             # ID hi public key hai (email, roll no, phone ...)
d_ID = extract(ID, s)                  # PKG ne Bob ko uska private key diya
print("Extract: Q_ID =", H1(ID), " d_ID =", d_ID)

# M = input("Enter message: ").encode()
#   .encode() -> string ko bytes, kyunki XOR bytes pe hota hai
M = "Meet me at 5 PM".encode()
U, V = encrypt(M, ID, P_pub)           # tuple unpack: U (number), V (bytes)
# V.hex() -> bytes ko readable hex string: b'\x0f\xa1' -> '0fa1'
print("Encrypt: U =", U, " V =", V.hex())
# .decode() -> bytes ko wapas string (encode ka ulta)
print("Decrypt:", decrypt(U, V, d_ID).decode())

# Eve ka private key (alag ID) -> alag K -> galat keystream -> garbage bytes.
# Garbage valid UTF-8 nahi hoga, isliye .decode() nahi kiya, raw bytes print kiye.
print("\nDecrypt with Eve's key:", decrypt(U, V, extract("eve@example.com", s)))


# =====================================================================
# PART 2: EXAM VERSION (bina comments - yahi likhna hai / ratna hai)
# =====================================================================
print("\n===== PART 2: Exam version =====")

import random, hashlib

q, p, g, P = 1019, 2039, 4, 7


def e(X, Y):
    return pow(g, X * Y % q, p)


def H1(ID):
    return int(hashlib.sha256(ID.encode()).hexdigest(), 16) % (q - 1) + 1


def H2(x, length):
    return hashlib.shake_256(str(x).encode()).digest(length)


def xor(a, b):
    return bytes(i ^ j for i, j in zip(a, b))


def extract(ID, s):
    return s * H1(ID) % q


def encrypt(M, ID, P_pub):
    r = random.randint(1, q - 1)
    K = pow(e(H1(ID), P_pub), r, p)
    return r * P % q, xor(M, H2(K, len(M)))


def decrypt(U, V, d):
    return xor(V, H2(e(d, U), len(V)))


s = random.randint(1, q - 1)
P_pub = s * P % q
print("Setup  : master key s =", s, " P_pub =", P_pub)

ID = input("Enter receiver's ID: ")
d_ID = extract(ID, s)
print("Extract: Q_ID =", H1(ID), " d_ID =", d_ID)

M = input("Enter message: ").encode()
U, V = encrypt(M, ID, P_pub)
print("Encrypt: U =", U, " V =", V.hex())
print("Decrypt:", decrypt(U, V, d_ID).decode())
print("\nDecrypt with Eve's key:", decrypt(U, V, extract("eve@example.com", s)))
