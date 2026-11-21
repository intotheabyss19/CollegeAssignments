"""
=====================================================================
 11. Bilinear Pairing using an Algebraic Pairing Model
=====================================================================

>> Bilinear Pairing kya hai? (Purpose)
   - Pairing ek special function hai jo DO points leta hai aur EK number deta hai:
         e : G1 x G1 -> GT
       G1 = ek group (real life mein elliptic curve ke points)
       GT = "target group" (ek finite field ke numbers, multiplication wala group)
   - Iski magic property: points ke andar chhupe "multipliers" bahar exponent
     mein aa jaate hain:
         e(aP, bQ) = e(P, Q)^(a*b)
   - Problem jo solve karta hai: normal ECC mein aP aur bP dekh ke "ab" ke
     baare mein kuch check nahi kar sakte. Pairing se aisi equations CHECK kar
     sakte hain bina a, b jaane. Isi se naye protocols bante hain:
     Identity-Based Encryption (Exp 12), short (BLS) signatures, 3-party DH.

>> Pairing ki 3 properties (ratt lo - viva ka favourite)
   1. BILINEAR:      e(aP, bQ) = e(P, Q)^(ab)
                     iska matlab additive form bhi:
                     e(P1 + P2, Q) = e(P1, Q) * e(P2, Q)
   2. NON-DEGENERATE: e(P, P) != 1  (warna sab kuch 1 aata, function bekaar)
   3. COMPUTABLE:    e efficiently (jaldi) calculate ho sake.
   (Symmetric pairing mein e(P, Q) = e(Q, P) bhi hota hai.)

>> Real pairing vs yeh "algebraic model"
   REAL: Weil pairing ya Tate pairing - special elliptic curves
         (pairing-friendly, jaise supersingular / BN / BLS12-381) pe,
         Miller's algorithm se compute hota hai. Code bahut lamba hai.
   MODEL (jo hum likhenge): structure same, maths simple
     - q = prime (group order), p = 2q + 1 (prime), toh q | (p - 1)
     - G1 = Z_q,  generator P.  "Point" aP ko sirf number  a*P mod q  se store karte hain
     - GT = Z_p* ka order-q subgroup, generator g (yahan g = 4, kyunki 4^q mod p = 1)
     - Pairing:  e(X, Y) = g^(X*Y mod q) mod p
     - Check: e(aP, bP) = g^(aP * bP) = g^(P*P*ab) = (g^(P*P))^(ab) = e(P, P)^(ab) ✓

>> Model INSECURE kyun hai?
   - G1 = Z_q mein "discrete log" trivial hai: X = a*P mod q diya ho toh
     a = X * P^(-1) mod q - bas ek division! Real ECC mein yeh mushkil hota hai.
   - Isliye model sirf PROPERTIES DIKHANE ke liye hai, real security ke liye nahi.

>> Parameters (lab wale - ratt lo)
   q = 1019, p = 2039 (= 2q + 1), g = 4, P = 7
   e(P, P) = 4^(49) mod 2039 = 147

>> Kahan use hota hai?
   - Identity-Based Encryption (Boneh-Franklin) -> Exp 12
   - BLS signatures (Ethereum 2.0 / blockchain mein signature aggregation)
   - Joux ka one-round 3-party Diffie-Hellman
   - zk-SNARKs (zero-knowledge proofs, Zcash), attribute-based encryption

>> Exam trick
   "e(X, Y) = pow(g, X*Y % q, p)"  -> ek line ka function.
   Phir 4 checks print karo: Bilinear, Additive, Symmetric, Non-degenerate.

>> Viva Questions
   Q1. Bilinear pairing kya hai?
       Ans: Map e: G1 x G1 -> GT jo bilinear, non-degenerate aur computable ho.
   Q2. Bilinearity ka matlab?
       Ans: e(aP, bQ) = e(P, Q)^(ab) - scalars exponent mein aa jaate hain.
   Q3. Non-degenerate kyun zaroori hai?
       Ans: Agar e(P, P) = 1 ho toh har pairing 1 dega (1^ab = 1), koi info nahi.
   Q4. Real life mein kaunse pairings use hote hain?
       Ans: Weil aur Tate pairing (aur unke fast versions jaise Ate, Optimal Ate).
   Q5. Pairing compute karne ka algorithm?
       Ans: Miller's algorithm.
   Q6. Har elliptic curve pe pairing use kar sakte hain?
       Ans: Nahi, "pairing-friendly" curves chahiye jinka embedding degree chhota
            ho (jaise BN254, BLS12-381, supersingular curves).
   Q7. Aapka model secure kyun nahi hai?
       Ans: G1 = Z_q mein discrete log ek division se mil jaata hai.
   Q8. Pairing ki wajah se ECC pe kaunsa attack hota hai?
       Ans: MOV attack - pairing se ECDLP ko finite field ke DLP mein convert
            kar dete hain jo aasaan hai. Isliye normal ECC curves pairing-friendly
            nahi chune jaate.
   Q9. Symmetric aur asymmetric pairing mein fark?
       Ans: Symmetric: G1 x G1 -> GT, e(P,Q) = e(Q,P). Asymmetric: G1 x G2 -> GT,
            do alag groups (modern curves jaise BLS12-381 asymmetric hain).
   Q10. Pairing ke applications?
       Ans: IBE, BLS short signatures, 3-party key agreement, zk-SNARKs.
   Q11. q | (p - 1) kyun chahiye?
       Ans: Tabhi Z_p* mein order-q subgroup (GT) exist karta hai.
"""


# =====================================================================
# PART 1: CODE SAMJHO (Part 2 wala code + har line ka manual)
# =====================================================================
# Neeche bilkul wahi code hai jo PART 2 mein hai, bas har line ke saath
# explanation. Sirf ek farak: input() ki jagah fixed value di hai (taaki
# file chalane pe do baar input na maange). Asli input() line comment mein hai.
print("===== PART 1: Annotated version =====")

# Koi import nahi chahiye - sirf built-in pow() use hota hai.
#
# Parameters (tuple unpacking, ek line mein chaar values):
#   q = 1019 -> prime, G1 aur GT dono groups ka order
#   p = 2039 -> prime, p = 2q + 1 -> isliye q, (p - 1) ko divide karta hai
#               aur Z_p* ke andar order q ka subgroup exist karta hai (yahi GT hai)
#   g = 4    -> GT ka generator (4 = 2^2 ek square hai -> uska order q hai, 1 nahi)
#   P = 7    -> G1 ka generator. G1 = Z_q, point "aP" ko number a*P mod q se store karte hain
q, p, g, P = 1019, 2039, 4, 7


# --- Pairing function e: G1 x G1 -> GT -----------------------------------
# e(X, Y) = g^(X*Y mod q) mod p
#   Kyun? Agar X = aP aur Y = bP, toh X*Y = ab*P^2 -> exponent mein ab aata hai,
#   isliye e(aP, bP) = e(P, P)^(ab)  -> yahi BILINEARITY hai.
#   X * Y % q -> exponent ko mod q rakha, kyunki g^q = 1 (g ka order q hai)
#   pow(g, exp, p) -> built-in: (g ** exp) % p fast tareeke se
def e(X, Y):
    return pow(g, X * Y % q, p)


# a = int(input("Enter a: "))
# b = int(input("Enter b: "))
#   input() string deta hai -> int(...) se number banaya
a = 5
b = 9

# X = aP, Y = bP  (G1 mein points). Tuple unpacking: X = 5*7 % 1019 = 35, Y = 63
X, Y = a * P % q, b * P % q
print("aP =", X, " bP =", Y)
print("e(P, P) =", e(P, P))                   # g^(P*P) = 4^49 mod 2039
print("e(aP, bP) =", e(X, Y))                   # left side
print("e(P, P)^(ab) =", pow(e(P, P), a * b, p))    # right side -> dono same aane chahiye

# --- Properties check (har line True deni chahiye) -----------------------
# 1. Bilinear: e(aP, bP) == e(P, P)^(ab)   -> scalars a, b exponent mein bahar aa jaate hain
print("Bilinear:", e(X, Y) == pow(e(P, P), a * b, p))
# 2. Additive (linear in first argument): e(X + Y, P) == e(X, P) * e(Y, P)
#    G1 mein addition (X + Y) % q  ->  GT mein multiplication (... * ...) % p ban jaata hai
print("Additive:", e((X + Y) % q, P) == e(X, P) * e(Y, P) % p)
# 3. Symmetric: e(X, Y) == e(Y, X)  -> X*Y = Y*X, toh order se farak nahi padta
print("Symmetric:", e(X, Y) == e(Y, X))
# 4. Non-degenerate: e(P, P) != 1  -> warna har pairing 1 aata, pairing bekaar hoti
print("Non-degenerate:", e(P, P) != 1)


# =====================================================================
# PART 2: EXAM VERSION (bina comments - yahi likhna hai / ratna hai)
# =====================================================================
print("\n===== PART 2: Exam version =====")

q, p, g, P = 1019, 2039, 4, 7


def e(X, Y):
    return pow(g, X * Y % q, p)


a = int(input("Enter a: "))
b = int(input("Enter b: "))
X, Y = a * P % q, b * P % q
print("aP =", X, " bP =", Y)
print("e(P, P) =", e(P, P))
print("e(aP, bP) =", e(X, Y))
print("e(P, P)^(ab) =", pow(e(P, P), a * b, p))

print("Bilinear:", e(X, Y) == pow(e(P, P), a * b, p))
print("Additive:", e((X + Y) % q, P) == e(X, P) * e(Y, P) % p)
print("Symmetric:", e(X, Y) == e(Y, X))
print("Non-degenerate:", e(P, P) != 1)
