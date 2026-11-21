"""
=====================================================================
 8. Elliptic-Curve Arithmetic over a Prime Field
    (Point Addition, Point Doubling, Scalar Multiplication)
=====================================================================

>> ECC kya hai? (Purpose)
   - Elliptic Curve Cryptography (ECC) ek PUBLIC-KEY system hai, RSA jaisa,
     lekin numbers ke jagah CURVE ke POINTS pe kaam karta hai.
   - Curve ka equation (prime field Fp ke upar):
         y^2 ≡ x^3 + a*x + b   (mod p)
     Condition: 4a^3 + 27b^2 ≠ 0 (mod p)  -> curve "smooth" ho (no cusp/self-cross)
   - Is experiment mein hum ECC ke BASIC OPERATIONS banate hain. Exp 9 (ECDH)
     aur Exp 10 (ECDSA) isi pe khade hain. Yeh unki "foundation" hai.

>> Security kis cheez pe tiki hai? (ECDLP)
   - k aur G diye hon toh Q = k*G nikalna aasaan hai (double-and-add).
   - Lekin sirf G aur Q diye hon toh k nikalna bahut mushkil hai.
     Isko kehte hain Elliptic Curve Discrete Logarithm Problem (ECDLP).
   - k = private key, Q = k*G = public key.

>> Algorithm (3 operations)
   O = "point at infinity" = identity element (jaise addition mein 0).
       P + O = P,   P + (-P) = O,   jahan -P = (x, -y mod p)

   1. POINT ADDITION  (P ≠ Q):  P = (x1, y1), Q = (x2, y2)
        λ  = (y2 - y1) / (x2 - x1)   mod p      (chord ka slope)
        x3 = λ^2 - x1 - x2           mod p
        y3 = λ(x1 - x3) - y1         mod p

   2. POINT DOUBLING  (P = Q):
        λ  = (3*x1^2 + a) / (2*y1)   mod p      (tangent ka slope)
        x3, y3 -> same formula jaisa upar

      NOTE: mod p mein "divide" nahi hota -> multiply by INVERSE:
            a / b mod p = a * pow(b, -1, p) mod p

   3. SCALAR MULTIPLICATION  k*P = P + P + ... + P (k times)
        k times add karna slow hai (k bahut bada hota hai).
        DOUBLE-AND-ADD use karo (jaise fast exponentiation):
          R = O
          k ke har bit ke liye (LSB se):
              agar bit = 1:  R = R + P
              P = 2P                       (double)
        Sirf ~log2(k) steps.

>> Haath se chhota example (written exam ke liye ratt lo)
   Curve: y^2 = x^3 + 2x + 2 (mod 17),  G = (5, 1)
   Check G curve pe hai:  1^2 = 1,  5^3 + 2*5 + 2 = 137 = 8*17 + 1 -> 1  ✓

   2G (doubling):
     λ  = (3*5^2 + 2) / (2*1) = 77 / 2 mod 17
        77 mod 17 = 9,  2^(-1) mod 17 = 9   (2*9 = 18 ≡ 1)
        λ = 9 * 9 = 81 mod 17 = 13
     x3 = 13^2 - 5 - 5 = 159 mod 17 = 6
     y3 = 13*(5 - 6) - 1 = -14 mod 17 = 3
     2G = (6, 3)  ✓

   3G = G + 2G (addition):
     λ  = (3 - 1) / (6 - 5) = 2
     x3 = 2^2 - 5 - 6 = -7 mod 17 = 10
     y3 = 2*(5 - 10) - 1 = -11 mod 17 = 6
     3G = (10, 6)  ✓

   G ka order = 19 -> 19G = O, 20G = G (cycle repeat).

>> Kyun kaam karta hai? (intuition)
   - Curve pe do points ko line se jodo -> line curve ko teesre point pe
     kaatti hai -> uska reflection (y -> -y) = P + Q.
   - Doubling mein dono point same hain, toh line ki jagah TANGENT lete hain.
   - Yeh "addition" ek GROUP banata hai (closure, identity O, inverse -P,
     associative). Isliye k*G meaningful hai aur cycle karta hai.

>> Kahan use hota hai?
   - ECDH (key exchange) -> Exp 9,  ECDSA (signatures) -> Exp 10
   - TLS/HTTPS (ECDHE), SSH (ed25519), Signal/WhatsApp
   - Bitcoin/Ethereum: curve secp256k1 (y^2 = x^3 + 7)
   - Smart cards, IoT - kyunki chhoti keys, kam computation.

>> Exam trick (yaad rakhne ke liye)
   "Same point? tangent (3x²+a)/2y : warna chord (y2-y1)/(x2-x1)"
   "x3 = λ² - x1 - x2,  y3 = λ(x1 - x3) - y1"
   (Code mein λ ka naam "slope" hai: slope = top * pow(bottom, -1, p) % p)
   mul = "result = O; while k > 0: k odd -> add, P double, k = k // 2"

>> Viva Questions
   Q1. ECC ka RSA pe kya fayda hai?
       Ans: Same security, bahut chhoti key. 256-bit ECC ≈ 3072-bit RSA.
            Fast, kam memory/bandwidth.
   Q2. ECC ki security kis problem pe based hai?
       Ans: ECDLP - Q = kG diya ho toh k nikalna mushkil hai.
   Q3. Point at infinity kya hai?
       Ans: Group ka identity element O. P + O = P aur P + (-P) = O.
            Vertical line curve ko "infinity" pe milti hai.
   Q4. Point ka order kya hota hai?
       Ans: Sabse chhota n jiske liye nG = O. Yahan G ka order 19 hai.
   Q5. Doubling aur addition ke formula mein kya farak hai?
       Ans: Sirf slope λ: doubling mein tangent (3x²+a)/2y,
            addition mein chord (y2-y1)/(x2-x1). x3, y3 same formula.
   Q6. Mod p mein division kaise karte ho?
       Ans: Modular inverse se: a/b = a * b^(-1) mod p.
            b^(-1) Extended Euclid se, ya Fermat se b^(p-2) mod p.
   Q7. Double-and-add kyun? k baar add kyun nahi?
       Ans: k ~ 2^256 ho sakta hai, k baar add impossible. Double-and-add
            sirf ~log2(k) (~256) steps leta hai.
   Q8. -P kya hota hai?
       Ans: P = (x, y) ho toh -P = (x, -y mod p). x-axis pe reflection.
   Q9. Prime field kyun use karte hain?
       Ans: Har non-zero element ka inverse exist karta hai, toh slope ka
            division hamesha possible hai.
   Q10. 4a³ + 27b² ≠ 0 condition kyun?
       Ans: Curve "singular" na ho (cusp ya self-intersection na ho),
            warna group law kaam nahi karta.
   Q11. Bitcoin kaunsa curve use karta hai?
       Ans: secp256k1: y² = x³ + 7 (a = 0, b = 7) over 256-bit prime.
"""


# =====================================================================
# PART 1: CODE SAMJHO (Part 2 wala code + har line ka manual)
# =====================================================================
# Neeche bilkul wahi code hai jo PART 2 mein hai, bas har line ke saath
# explanation. Sirf ek farak: input() ki jagah fixed value di hai (taaki
# file chalane pe do baar input na maange). Asli input() line comment mein hai.
print("===== PART 1: Annotated version =====")

# Koi import nahi - sirf built-in pow() chahiye.

# Curve: y^2 ≡ x^3 + ax + b (mod p)  ->  y^2 = x^3 + 2x + 2 (mod 17)
# Tuple unpacking: p = 17, a = 2, b = 2
p, a, b = 17, 2, 2
# G = base point (generator). Point ko Python tuple (x, y) se represent karte hain.
# Check: 1^2 = 1, aur 5^3 + 2*5 + 2 = 137 = 8*17 + 1 -> 1  ✓ (curve pe hai)
G = (5, 1)


# --- Point curve pe hai ya nahi ---------------------------------------
def on_curve(P):
    # None = POINT AT INFINITY (O). Yeh group ka "zero" hai: P + O = P.
    # Iska koi (x, y) nahi hota, isliye Python ka None use kiya. O hamesha "curve pe" maana jaata hai.
    if P is None:
        return True
    x, y = P                           # tuple unpacking: (5, 1) -> x = 5, y = 1
    # y^2 - (x^3 + ax + b) ka mod p zero hona chahiye. x ** 3 = x cube.
    return (y * y - x ** 3 - a * x - b) % p == 0


# --- Point addition + doubling (ek hi function) -------------------------
def add(P, Q):
    # O identity hai: O + Q = Q, P + O = P  (None = point at infinity O)
    if P is None:
        return Q
    if Q is None:
        return P
    # Tuple unpacking: P = (5, 1) -> x1 = 5, y1 = 1. Same Q ke liye.
    x1, y1 = P
    x2, y2 = Q
    # P + (-P) = O: -P = (x, -y). Same x aur y1 + y2 ≡ 0 (mod p) matlab dono
    # points ek hi vertical line pe hain -> line curve ko teesri jagah nahi kaatti
    # -> answer "infinity" pe hai = O.  (y = 0 wale point ko double karna bhi yahi case hai.)
    if x1 == x2 and (y1 + y2) % p == 0:
        return None
    # Slope = top / bottom:
    #   P == Q (DOUBLING):  (3x1^2 + a) / (2y1)     <- tangent line ka slope (calculus: dy/dx)
    #   P != Q (ADDITION):  (y2 - y1) / (x2 - x1)   <- do points ko jodne wali line ka slope
    if P == Q:
        top = 3 * x1 * x1 + a
        bottom = 2 * y1
    else:
        top = y2 - y1
        bottom = x2 - x1
    # Mod p mein "divide" nahi hota -> bottom ke inverse se multiply karte hain:
    #   pow(x, -1, p) = x ka modular inverse (x * inv % p == 1). Python 3.8+.
    #   Example: pow(2, -1, 17) = 9 kyunki 2 * 9 = 18 ≡ 1 (mod 17).
    #   Agar x ≡ 0 (mod p) ho toh inverse nahi hota -> ValueError. Upar wali
    #   P + (-P) check isi case ko pehle hi pakad leti hai.
    slope = top * pow(bottom, -1, p) % p
    # Line curve ko teesre point pe kaatti hai, use x-axis pe reflect karo:
    #   x3 = slope^2 - x1 - x2
    #   y3 = slope * (x1 - x3) - y1      (minus y1 = reflection)
    # % p se sab 0..p-1 mein rehta hai (negative bhi positive ban jaata hai).
    x3 = (slope * slope - x1 - x2) % p
    y3 = (slope * (x1 - x3) - y1) % p
    return (x3, y3)
    # Example 2G: top = 3*25 + 2 = 77, bottom = 2, inverse(2) = 9
    #             slope = 77 * 9 = 693 % 17 = 13
    #             x3 = 169 - 10 = 159 % 17 = 6,  y3 = 13*(5-6) - 1 = -14 % 17 = 3  -> (6, 3)


# --- Scalar multiplication kP: DOUBLE-AND-ADD --------------------------
# kP = P + P + ... (k baar) -> k bada ho (256-bit) toh k additions impossible.
# Trick: k ko binary mein dekho. Har step pe P double karo; k ka last bit 1 ho
# (k odd ho) toh result mein add karo. Sirf ~log2(k) steps (RSA ke square-and-multiply jaisa).
def mul(k, P):
    result = None                      # result shuru mein O (zero)
    while k > 0:                       # jab tak k ke bits bache hain
        # k % 2 == 1 -> k odd hai -> binary ka LAST bit 1 hai -> is P ko result mein jodo.
        if k % 2 == 1:
            result = add(result, P)
        P = add(P, P)                  # P -> 2P -> 4P -> 8P ...
        # k // 2 -> integer division, binary ka last bit hata deta hai. 13 (1101) -> 6 (110)
        k = k // 2
    return result
    # Trace k = 13 = 1101b (result shuru mein O, P = G):
    #   k = 13 odd  -> result = G        , P = 2G , k = 6
    #   k = 6  even -> (skip)            , P = 4G , k = 3
    #   k = 3  odd  -> result = G + 4G = 5G , P = 8G , k = 1
    #   k = 1  odd  -> result = 5G + 8G = 13G  ✓   (4 doublings + 3 additions, 12 nahi)


print("p, a, b =", p, a, b, " G =", G)
P = G
Q = add(G, G)                          # point DOUBLING: 2G = (6, 3)
print("P = G:", P)
print("Q = 2P:", Q)
print("P + Q:", add(P, Q))          # point ADDITION: G + 2G = 3G = (10, 6)
# Cross-check: double-and-add se 3G bhi wahi aana chahiye.
print("3G == P + Q:", mul(3, G) == add(P, Q))

# k = int(input("Enter scalar k: "))
#   int(...) kyunki input() string deta hai.
#   G ka order 19 hai -> 19G = O (None print hoga), 20G = G wapas. k = 0 -> None.
k = 7
R = mul(k, G)                          # 7G = (0, 6)
print("k * G =", R, " on curve:", on_curve(R))


# =====================================================================
# PART 2: EXAM VERSION (bina comments - yahi likhna hai / ratna hai)
# =====================================================================
print("\n===== PART 2: Exam version =====")

p, a, b = 17, 2, 2
G = (5, 1)


def on_curve(P):
    if P is None:
        return True
    x, y = P
    return (y * y - x ** 3 - a * x - b) % p == 0


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


print("p, a, b =", p, a, b, " G =", G)
P = G
Q = add(G, G)
print("P = G:", P)
print("Q = 2P:", Q)
print("P + Q:", add(P, Q))
print("3G == P + Q:", mul(3, G) == add(P, Q))

k = int(input("Enter scalar k: "))
R = mul(k, G)
print("k * G =", R, " on curve:", on_curve(R))
