"""
=====================================================================
 9. Elliptic Curve Diffie-Hellman (ECDH) Key Agreement
=====================================================================

>> ECDH kya hai? (Purpose)
   - KEY AGREEMENT protocol: do log (Alice, Bob) PUBLIC channel pe baat karke
     ek SAME SECRET KEY bana lete hain, bina key directly bheje.
   - Eavesdropper (Eve) sab messages dekh sakti hai, phir bhi key nahi bana sakti.
   - Yeh normal Diffie-Hellman (Exp 5) ka elliptic curve version hai:
        DH:   A = g^a mod p,   shared = B^a mod p
        ECDH: Q_A = d_A * G,   shared = d_A * Q_B
     (exponent ki jagah scalar multiplication, multiply ki jagah point add)
   - Shared key ke baad data AES jaise symmetric cipher se encrypt hota hai.

>> Security kis cheez pe tiki hai?
   - ECDLP: G aur Q = d*G diye hon toh d nikalna mushkil hai.
   - Eve ke paas Q_A aur Q_B hain, lekin d_A*d_B*G banane ke liye d_A ya d_B
     chahiye (ECDH problem).

>> Algorithm
   PUBLIC (sabko pata): curve (p, a, b), base point G, G ka order n

   1. Alice: private d_A = random in [1, n-1],  public Q_A = d_A * G
   2. Bob:   private d_B = random in [1, n-1],  public Q_B = d_B * G
   3. Q_A aur Q_B public channel pe exchange karo
   4. Alice: S = d_A * Q_B
      Bob:   S = d_B * Q_A
   5. Dono ka S SAME hai -> shared secret (usually S ka x-coordinate,
      hash karke AES key bana lete hain)

>> Haath se chhota example (Exp 8 wala curve: y^2 = x^3+2x+2 mod 17, G=(5,1), n=19)
   d_A = 3  -> Q_A = 3G = (10, 6)
   d_B = 2  -> Q_B = 2G = (6, 3)
   Alice: S = 3 * Q_B = 3 * 2G = 6G
   Bob:   S = 2 * Q_A = 2 * 3G = 6G      -> same point  ✓
   (6G = (16, 13))

>> Kyun kaam karta hai? (intuition)
   d_A * Q_B = d_A * (d_B * G) = (d_A * d_B) * G
   d_B * Q_A = d_B * (d_A * G) = (d_B * d_A) * G
   Scalar multiplication commutative hai -> dono same.

>> Kahan use hota hai?
   - TLS 1.3 / HTTPS: ECDHE (Ephemeral ECDH, har session nayi key)
   - Signal, WhatsApp (X25519), SSH key exchange, VPNs (WireGuard)
   - Bluetooth pairing

>> Exam trick (yaad rakhne ke liye)
   "private = random, public = d*G, shared = my_private * their_public"
   Exp 8 ka add + mul copy karo, upar se bas 4 lines: dA, dB, QA = dA*G, QB = dB*G,
   phir SA = dA*QB, SB = dB*QA.

>> Viva Questions
   Q1. ECDH encryption algorithm hai?
       Ans: Nahi. Sirf KEY AGREEMENT hai. Shared key se baad mein AES
            jaisa cipher encryption karta hai.
   Q2. ECDH ki security kis problem pe hai?
       Ans: ECDLP / ECDH problem - d*G se d nikalna mushkil.
   Q3. DH aur ECDH mein farak?
       Ans: DH modular exponentiation (g^a mod p) use karta hai, ECDH
            point multiplication (d*G). ECDH ko chhoti key chahiye
            (256-bit ECDH ≈ 3072-bit DH).
   Q4. Man-in-the-Middle (MITM) attack kya hai?
       Ans: Eve beech mein baith ke Alice se apni key aur Bob se apni key
            exchange kar leti hai. Dono samajhte hain ek doosre se baat ho
            rahi hai. Plain ECDH mein AUTHENTICATION nahi hai.
   Q5. MITM se kaise bachein?
       Ans: Public keys ko authenticate karo - digital signatures (ECDSA),
            certificates (PKI). TLS mein yahi hota hai.
   Q6. Ephemeral ECDH (ECDHE) kya hai? Fayda?
       Ans: Har session ke liye naye random keys. Forward secrecy milti hai -
            baad mein long-term key leak ho bhi jaye toh purane sessions
            safe rehte hain.
   Q7. Private key kis range mein choose karte ho?
       Ans: 1 se n-1, jahan n = G ka order.
   Q8. Received public key ko check kyun karna chahiye?
       Ans: Invalid-curve attack se bachne ke liye - point curve pe hai
            aur O nahi hai, yeh verify karna chahiye.
   Q9. Shared point se actual key kaise banti hai?
       Ans: Usually x-coordinate lekar KDF/hash (jaise SHA-256) se
            AES key derive karte hain.
   Q10. n prime kyun hona chahiye?
       Ans: Prime order subgroup mein har non-O point generator hota hai,
            small-subgroup attacks nahi chalte.
"""


# =====================================================================
# PART 1: CODE SAMJHO (Part 2 wala code + har line ka manual)
# =====================================================================
# Neeche bilkul wahi code hai jo PART 2 mein hai, bas har line ke saath
# explanation. Is program mein input() nahi hai (private keys random hain),
# isliye output har run pe alag aayega - bas "Keys match: True" hona chahiye.
print("===== PART 1: Annotated version =====")

# random module (built-in): random numbers ke liye.
#   random.randint(a, b) -> a aur b ke beech random integer, DONO ends INCLUDED.
#   random.randint(1, 5) -> 1, 2, 3, 4 ya 5.
# (Real crypto mein 'secrets' module use karte hain - random predictable hai. Lab ke liye theek.)
import random

# Public parameters (sabko pata hote hain):
#   Curve y^2 = x^3 + 2x + 30 (mod 10007), base point G, aur n = G ka order (nG = O).
#   n prime hai (10091) -> har private key 1..n-1 valid hai.
p, a, b = 10007, 2, 30
G = (1, 283)                           # check: 283^2 = 80089 ≡ 33 = 1 + 2 + 30 (mod 10007) ✓
n = 10091


# --- Exp 8 wala point addition (same code) -------------------------------
def add(P, Q):
    # None = point at infinity O (identity): O + Q = Q
    if P is None: return Q
    if Q is None: return P
    (x1, y1), (x2, y2) = P, Q          # P = (x1, y1), Q = (x2, y2)
    # P + (-P) = O (vertical line, teesra point infinity pe)
    if x1 == x2 and (y1 + y2) % p == 0: return None
    # slope: doubling -> (3x^2 + a)/(2y),  addition -> (y2 - y1)/(x2 - x1)
    # pow(x, -1, p) = modular inverse ("divide" ki jagah), x ≡ 0 pe ValueError
    if P == Q: l = (3 * x1 * x1 + a) * pow(2 * y1, -1, p) % p
    else: l = (y2 - y1) * pow(x2 - x1, -1, p) % p
    x3 = (l * l - x1 - x2) % p         # x3 = l^2 - x1 - x2
    return (x3, (l * (x1 - x3) - y1) % p)   # y3 = l(x1 - x3) - y1


# --- Exp 8 wala double-and-add (same code) -------------------------------
def mul(k, P):
    R = None
    while k:
        if k & 1: R = add(R, P)        # k & 1 = last bit; 1 ho toh add
        P = add(P, P)                  # har step pe double
        k >>= 1                        # last bit hatao (k // 2)
    return R


# --- Step 1: Dono apni private key chunte hain ---------------------------
# Private key d = random number 1..n-1 (0 nahi, kyunki 0*G = O; n bhi nahi, nG = O).
dA = random.randint(1, n - 1)          # Alice ka secret
dB = random.randint(1, n - 1)          # Bob ka secret

# --- Step 2: Public key = d * G (scalar multiplication) ------------------
# Q_A = dA*G public bhej sakte hain - Q_A aur G se dA nikalna = ECDLP (bahut mushkil).
QA = mul(dA, G)
QB = mul(dB, G)
print(f"Curve: y^2 = x^3 + {a}x + {b} (mod {p}), G = {G}, n = {n}")
print("Alice: private d_A =", dA, " public Q_A =", QA)
print("Bob  : private d_B =", dB, " public Q_B =", QB)

# --- Step 3: Public keys exchange, phir apni private key se multiply ------
# Alice: dA * QB = dA * (dB * G)
# Bob  : dB * QA = dB * (dA * G)
# Dono = (dA * dB) * G -> SAME point. Eve ke paas sirf QA, QB hain, dA/dB nahi.
SA = mul(dA, QB)
SB = mul(dB, QA)
print("Alice's shared key:", SA)
print("Bob's shared key  :", SB)
print("Keys match:", SA == SB)         # tuples compare: x aur y dono same -> True
# Real life mein shared point ka x-coordinate hash karke AES key banate hain.


# =====================================================================
# PART 2: EXAM VERSION (bina comments - yahi likhna hai / ratna hai)
# =====================================================================
print("\n===== PART 2: Exam version =====")

import random

p, a, b = 10007, 2, 30
G = (1, 283)
n = 10091


def add(P, Q):
    if P is None: return Q
    if Q is None: return P
    (x1, y1), (x2, y2) = P, Q
    if x1 == x2 and (y1 + y2) % p == 0: return None
    if P == Q: l = (3 * x1 * x1 + a) * pow(2 * y1, -1, p) % p
    else: l = (y2 - y1) * pow(x2 - x1, -1, p) % p
    x3 = (l * l - x1 - x2) % p
    return (x3, (l * (x1 - x3) - y1) % p)


def mul(k, P):
    R = None
    while k:
        if k & 1: R = add(R, P)
        P = add(P, P)
        k >>= 1
    return R


dA = random.randint(1, n - 1)
dB = random.randint(1, n - 1)
QA = mul(dA, G)
QB = mul(dB, G)
print(f"Curve: y^2 = x^3 + {a}x + {b} (mod {p}), G = {G}, n = {n}")
print("Alice: private d_A =", dA, " public Q_A =", QA)
print("Bob  : private d_B =", dB, " public Q_B =", QB)

SA = mul(dA, QB)
SB = mul(dB, QA)
print("Alice's shared key:", SA)
print("Bob's shared key  :", SB)
print("Keys match:", SA == SB)
