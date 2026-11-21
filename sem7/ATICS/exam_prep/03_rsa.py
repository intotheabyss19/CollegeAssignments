"""
=====================================================================
 3. RSA Public-Key Encryption and Decryption
=====================================================================

>> RSA kya hai? (Purpose)
   - RSA ek PUBLIC-KEY (asymmetric) cipher hai. Matlab do alag keys hoti hain:
       Public key  (e, n) -> sabko de do, isse koi bhi ENCRYPT kar sakta hai
       Private key (d, n) -> sirf apne paas, isse sirf tum DECRYPT kar sakte ho
   - Problem jo solve karta hai: DES/AES jaise symmetric ciphers mein dono
     taraf SAME key chahiye, toh key pehle secretly bhejni padti hai.
     RSA mein secret key share hi nahi karni padti.
   - Naam: Rivest, Shamir, Adleman (1977).

>> Security kis cheez pe tiki hai?
   - Do bade primes p, q ko multiply karna aasaan hai  (n = p * q)
   - Lekin sirf n diya ho toh p aur q nikalna (FACTORIZATION) bahut mushkil hai.
   - p, q pata nahi -> phi(n) pata nahi -> d pata nahi -> decrypt nahi kar sakte.

>> Algorithm (3 steps)
   KEY GENERATION:
     1. Do primes chuno: p, q
     2. n = p * q                      (modulus, public hota hai)
     3. phi = (p - 1) * (q - 1)        (Euler totient, SECRET)
     4. e chuno: 1 < e < phi aur gcd(e, phi) = 1     (common: 3, 17, 65537)
     5. d = e^(-1) mod phi   matlab  (d * e) % phi == 1
        -> d Extended Euclidean Algorithm se nikalte hain
     Public key = (e, n),  Private key = (d, n)

   ENCRYPTION:  c = m^e mod n        (m < n hona chahiye)
   DECRYPTION:  m = c^d mod n

>> Haath se chhota example (viva/written exam ke liye ratt lo)
   p = 61, q = 53
   n   = 61 * 53 = 3233
   phi = 60 * 52 = 3120
   e   = 17                 (gcd(17, 3120) = 1  ✓)
   d   = 2753               (17 * 2753 = 46801 = 15*3120 + 1  ✓)
   m = 65  ->  c = 65^17 mod 3233 = 2790
   c = 2790 -> m = 2790^2753 mod 3233 = 65  ✓

>> Kyun kaam karta hai? (intuition)
   c^d = (m^e)^d = m^(e*d) mod n
   e*d = 1 + k*phi  (kyunki d*e ≡ 1 mod phi)
   Euler's theorem: m^phi ≡ 1 (mod n)  ->  m^(1 + k*phi) = m * (m^phi)^k = m * 1 = m

>> Kahan use hota hai?
   - HTTPS/TLS handshake (purane versions mein key exchange, aaj bhi certificates mein)
   - Digital signatures (sign = private key se, verify = public key se) -> Exp 4
   - SSH keys, PGP email encryption
   - Practically RSA se seedha bada data encrypt nahi karte (slow hai) -
     RSA se AES ki key encrypt karte hain, phir data AES se ("hybrid encryption").

>> Exam trick (yaad rakhne ke liye)
   "p q -> n phi -> e d -> pow pow"
   Encrypt = pow(m, e, n), Decrypt = pow(c, d, n). Bas yahi do lines.
   d ke liye exam mein shortcut: d = pow(e, -1, phi)  (Python 3.8+ helper).
   Examiner gcd_ext maange toh PART 1 wala 4-line gcd_ext likho.

>> Viva Questions
   Q1. RSA symmetric hai ya asymmetric?
       Ans: Asymmetric (public-key). Encrypt aur decrypt ki keys alag hain.
   Q2. RSA ki security kis hard problem pe based hai?
       Ans: Integer factorization - n se p aur q nikalna mushkil hai.
   Q3. phi(n) kya hai aur RSA mein kyun chahiye?
       Ans: 1 se n tak n ke saath co-prime numbers ki count. n = p*q ke liye
            phi = (p-1)(q-1). Isi se d calculate hota hai.
   Q4. e ki condition kya hai?
       Ans: 1 < e < phi aur gcd(e, phi) = 1, warna e ka inverse (d) exist nahi karega.
   Q5. d kaise nikalte ho?
       Ans: Extended Euclidean Algorithm se: d = e^(-1) mod phi.
   Q6. e = 65537 hi kyun common hai?
       Ans: Prime hai, aur binary mein 10000000000000001 - sirf do 1 bits,
            toh m^e jaldi calculate hota hai. Saath hi bahut chhota e (jaise 3)
            kuch attacks ke liye risky hota hai.
   Q7. Message m ki condition?
       Ans: 0 <= m < n. Bada message ho toh tod ke blocks mein bhejo.
   Q8. Textbook RSA ki kamzori?
       Ans: Deterministic hai - same m ka hamesha same c. Isliye real life mein
            padding (OAEP) use karte hain jo randomness add karta hai.
   Q9. Real RSA mein key size kitna hota hai?
       Ans: n kam se kam 2048 bits (p, q ~1024 bits each).
   Q10. Agar attacker n factor kar le toh?
       Ans: p, q mil gaye -> phi mil gaya -> d mil gaya -> RSA broken.
"""


# =====================================================================
# PART 1: CODE SAMJHO (Part 2 wala code + har line ka manual)
# =====================================================================
# Neeche bilkul wahi code hai jo PART 2 mein hai, bas har line ke saath
# explanation. Sirf ek farak: input() ki jagah fixed value di hai (taaki
# file chalane pe do baar input na maange). Asli input() line comment mein hai.
print("===== PART 1: Annotated version =====")

# --- Key generation ---------------------------------------------------
# p, q = do prime numbers (asli RSA mein ~1024-bit, yahan chhote taaki
# haath se check kar sako). e = public exponent.
# Ek line mein teen variables: "tuple unpacking" -> p=61, q=53, e=17
p, q, e = 61, 53, 17

# n = modulus. Public key aur private key DONO mein yahi n aata hai.
n = p * q                              # 61 * 53 = 3233

# phi = Euler totient of n. Yeh SECRET hai - sirf p, q jaanne wala nikal sakta hai.
phi = (p - 1) * (q - 1)                # 60 * 52 = 3120

# d = e ka modular inverse mod phi, matlab (d * e) % phi == 1
#
# pow(base, exp, mod)  -> Python ka BUILT-IN function (import nahi karna padta)
#   - 2 arguments: pow(a, b)       = a ** b
#   - 3 arguments: pow(a, b, m)    = (a ** b) % m, lekin FAST tareeke se
#                                    (square-and-multiply, beech mein hi % m
#                                    karta rehta hai, toh number kabhi bada nahi hota)
#   - exp = -1 dena (Python 3.8+): pow(e, -1, phi) = e ka modular inverse.
#     Agar inverse exist nahi karta (gcd(e, phi) != 1) toh ValueError deta hai.
#     Andar se yeh wahi Extended Euclidean Algorithm chalata hai.
d = pow(e, -1, phi)                    # = 2753, check: 17 * 2753 % 3120 == 1
print("Public key:", (e, n), " Private key:", (d, n))

# --- Agar examiner bole "pow(e, -1, phi) mat use karo, inverse khud nikalo" ---
# Extended Euclid: gcd(a, b) ke saath s, t bhi deta hai jahan a*s + b*t = gcd.
# gcd_ext(e, phi) -> (1, s, t) aur e*s + phi*t = 1  ->  isliye d = s % phi
# Return: tuple (g, s, t). [1] se s nikalo, % phi se negative ko positive karo.
def gcd_ext(a, b):
    if b == 0:                         # base case: gcd(a, 0) = a  ->  a*1 + 0*0 = a
        return a, 1, 0
    g, s1, t1 = gcd_ext(b, a % b)      # Euclid jaisa: gcd(a, b) = gcd(b, a % b)
    return g, t1, s1 - (a // b) * t1   # wapas aate hue: s = t1, t = s1 - (a//b)*t1


assert gcd_ext(e, phi)[1] % phi == d   # dono tareeke same d dete hain

# --- Encryption / Decryption --------------------------------------------
# m = int(input("Enter integer message (< n): "))
#   input() hamesha STRING deta hai, isliye int(...) se number banaya.
m = 65

# RSA mein message n se chhota hona chahiye (0 <= m < n), warna mod n ke
# baad information kho jaati hai aur decrypt galat aayega. Yahi edge case check.
if not 0 <= m < n:
    print("Message must be between 0 and", n - 1)
else:
    c = pow(m, e, n)                   # ENCRYPT: c = m^e mod n  (public key (e, n) se)
    print("Encrypted:", c)             # 65 -> 2790
    print("Decrypted:", pow(c, d, n))  # DECRYPT: m = c^d mod n  (private key (d, n) se) -> 65

# Note: m ** e % n bhi sahi answer deta hai, lekin m ** e pehle poora
# calculate hota hai (bahut bada number) -> bade keys pe hang. Hamesha pow(m, e, n).


# =====================================================================
# PART 2: EXAM VERSION (bina comments - yahi likhna hai / ratna hai)
# =====================================================================
print("\n===== PART 2: Exam version =====")

p, q, e = 61, 53, 17
n = p * q
phi = (p - 1) * (q - 1)
d = pow(e, -1, phi)
print("Public key:", (e, n), " Private key:", (d, n))

m = int(input("Enter integer message (< n): "))
if not 0 <= m < n:
    print("Message must be between 0 and", n - 1)
else:
    c = pow(m, e, n)
    print("Encrypted:", c)
    print("Decrypted:", pow(c, d, n))
