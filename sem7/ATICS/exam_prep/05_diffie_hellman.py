"""
=====================================================================
 5. Diffie-Hellman Key Exchange
=====================================================================

>> Diffie-Hellman kya hai? (Purpose)
   - Yeh ek KEY EXCHANGE (key agreement) algorithm hai, encryption algorithm NAHI.
   - Problem: Alice aur Bob ko AES/DES jaisi symmetric cipher ke liye ek SAME
     secret key chahiye, lekin unke beech sirf public channel hai (internet),
     jahan attacker (Eve) sab kuch sun sakta hai.
   - DH se dono public channel pe sirf kuch numbers bhejte hain, aur end mein
     dono ke paas SAME secret key aa jaati hai - jo Eve calculate nahi kar sakti.
   - Naam: Whitfield Diffie aur Martin Hellman (1976) - pehla public-key idea.

>> Security kis cheez pe tiki hai?
   - DISCRETE LOGARITHM PROBLEM (DLP):
       g, p aur a diye hon toh  A = g^a mod p  nikalna aasaan hai.
       Lekin g, p aur A diye hon toh  a  nikalna bahut mushkil hai (bade p ke liye).
   - Eve ko A aur B dikhte hain, lekin a ya b nahi -> shared key nahi bana sakti.

>> Algorithm
   PUBLIC PARAMETERS (sabko pata):
     p = ek bada prime
     g = p ka primitive root (generator)
   STEPS:
     1. Alice secret a chunti hai (1 < a < p-1),  A = g^a mod p  -> Bob ko bhejti hai
     2. Bob   secret b chunta hai  (1 < b < p-1),  B = g^b mod p  -> Alice ko bhejta hai
     3. Alice:  K = B^a mod p
        Bob  :  K = A^b mod p
     Dono ka K same hoga.

>> Haath se chhota example (viva/written exam ke liye ratt lo)
   p = 23, g = 5
   Alice: a = 6   ->  A = 5^6  mod 23 = 8
   Bob  : b = 15  ->  B = 5^15 mod 23 = 19
   Alice: K = 19^6 mod 23 = 2
   Bob  : K = 8^15 mod 23 = 2      -> Shared key = 2  ✓

>> Kyun kaam karta hai? (intuition)
   Alice ka K = B^a = (g^b)^a = g^(ab) mod p
   Bob   ka K = A^b = (g^a)^b = g^(ab) mod p
   Power ka order badalne se answer nahi badalta -> dono same.
   Eve ke paas sirf g^a aur g^b hai. g^a * g^b = g^(a+b) milta hai, g^(ab) nahi.

>> Primitive root kya hota hai?
   g ek primitive root hai mod p agar g^1, g^2, ..., g^(p-1) mod p
   saare numbers 1 se p-1 tak (har ek exactly ek baar) bana de.
   Example: 5 mod 23 -> 22 alag values deta hai, isliye 5 primitive root hai.
   Isse key space poora use hota hai (keys predictable nahi hoti).

>> Kahan use hota hai?
   - HTTPS/TLS (DHE / ECDHE key exchange - har session ki nayi key)
   - SSH connection setup, VPN (IPsec IKE), Signal/WhatsApp (X3DH)
   - "Perfect Forward Secrecy": har session naye a, b -> purani key leak ho toh
     bhi purane sessions safe.

>> Kamzori: Man-in-the-Middle (MITM) attack
   - DH mein AUTHENTICATION nahi hai - Alice ko pata nahi ki B sach mein Bob ne bheja.
   - Eve beech mein baith ke Alice se ek key aur Bob se doosri key bana leti hai,
     aur dono ke messages padh ke aage forward karti hai.
   - Fix: public values ko SIGN karo (RSA/ECDSA signature, certificates) ->
     "Authenticated Diffie-Hellman" (TLS mein yahi hota hai).

>> Exam trick (yaad rakhne ke liye)
   "p g public, a b secret, A = g^a, B = g^b, K = B^a = A^b"
   Code mein sirf pow(g, a, p) aur pow(B, a, p). ECDH (Exp 9) bilkul same hai,
   bas pow ki jagah point multiplication aata hai.

>> Viva Questions
   Q1. DH encryption algorithm hai kya?
       Ans: Nahi. Yeh sirf key exchange hai. Shared key baad mein AES jaise
            symmetric cipher mein use hoti hai.
   Q2. DH ki security kis problem pe based hai?
       Ans: Discrete Logarithm Problem - g^a mod p se a nikalna mushkil hai.
            (Aur Computational DH problem - g^a, g^b se g^ab nikalna mushkil hai.)
   Q3. Public kya hai aur private kya?
       Ans: Public: p, g, A, B.  Private: a, b aur shared key K.
   Q4. Primitive root kyun chahiye?
       Ans: Taaki g^a mod p saare 1..p-1 values le sake. Chhota generator ho toh
            possible keys kam ho jaati hain aur brute force aasaan.
   Q5. DH pe sabse famous attack?
       Ans: Man-in-the-Middle, kyunki authentication nahi hai.
   Q6. MITM kaise rokte hain?
       Ans: Public values ko digitally sign karke / certificates use karke.
   Q7. Kya Eve A aur B ko multiply karke key bana sakti hai?
       Ans: Nahi. A*B = g^(a+b), jabki key g^(ab) hai.
   Q8. p kitna bada hona chahiye?
       Ans: Kam se kam 2048 bits. Chhote p pe discrete log jaldi nikal jaata hai.
   Q9. Forward secrecy kya hai?
       Ans: Har session mein naye random a, b (ephemeral DH). Long-term key leak
            hone pe bhi purane sessions decrypt nahi hote.
   Q10. DH aur RSA mein fark?
       Ans: RSA se encrypt/sign kar sakte ho (factorization pe based).
            DH sirf shared key banata hai (discrete log pe based).
"""


# =====================================================================
# PART 1: CODE SAMJHO (Part 2 wala code + har line ka manual)
# =====================================================================
# Neeche bilkul wahi code hai jo PART 2 mein hai, bas har line ke saath
# explanation. (Is program mein input() nahi hai, toh kuch replace nahi kiya.)
print("===== PART 1: Annotated version =====")

# random -> Python ka built-in module, random numbers ke liye.
#   random.randint(a, b) -> a se b tak koi bhi integer, DONO ends included.
#   randint(2, 21) -> 2, 3, ..., 21 mein se koi ek.
#   (Real crypto mein `secrets` module use karte hain; lab ke liye random theek hai.)
import random

# PUBLIC parameters - sabko pata hote hain (Eve ko bhi):
#   p = prime modulus, g = generator (primitive root mod p).
#   23 aur 5 textbook values hain: 5 ki powers mod 23 saare 1..22 deti hain.
p, g = 23, 5

# PRIVATE keys - Alice ka a, Bob ka b. Kabhi bhejte nahi.
#   Range 2 .. p-2: 1 aur p-1 avoid karte hain kyunki g^1 = g aur g^(p-1) = 1
#   (dono "weak" - public key se private turant pata chal jaata).
a = random.randint(2, p - 2)
b = random.randint(2, p - 2)

# PUBLIC keys - yeh network pe bhejte hain.
#   pow(base, exp, mod) -> built-in, (base ** exp) % mod FAST tareeke se.
#   A = g^a mod p,  B = g^b mod p
A = pow(g, a, p)
B = pow(g, b, p)
print("Public: p =", p, " g =", g)
print("Alice: private a =", a, " public A =", A)
print("Bob : private b =", b, " public B =", B)

# SHARED key - dono apni private key + doosre ki public key se banate hain:
#   Alice: K = B^a = (g^b)^a = g^(ab) mod p
#   Bob  : K = A^b = (g^a)^b = g^(ab) mod p     -> same!
# Eve ke paas sirf A, B hain; g^(ab) ke liye a ya b chahiye (Discrete Log problem).
K_A = pow(B, a, p)
K_B = pow(A, b, p)
print("Alice's shared key:", K_A)
print("Bob's shared key:", K_B)
print("Keys match:", K_A == K_B)    # hamesha True


# =====================================================================
# PART 2: EXAM VERSION (bina comments - yahi likhna hai / ratna hai)
# =====================================================================
print("\n===== PART 2: Exam version =====")

import random

p, g = 23, 5
a = random.randint(2, p - 2)
b = random.randint(2, p - 2)
A = pow(g, a, p)
B = pow(g, b, p)
print("Public: p =", p, " g =", g)
print("Alice: private a =", a, " public A =", A)
print("Bob : private b =", b, " public B =", B)

K_A = pow(B, a, p)
K_B = pow(A, b, p)
print("Alice's shared key:", K_A)
print("Bob's shared key:", K_B)
print("Keys match:", K_A == K_B)
