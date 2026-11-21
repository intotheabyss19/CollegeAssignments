# 8. Write a program to implement point addition, point doubling and scalar multiplication on Elliptic-Curve Arithmetic over a Prime Field.

# Curve: y^2 ≡ x^3 + ax + b (mod p)
p = 17
a = 2
b = 2
G = (5, 1)
O = None  # point at infinity (identity)


def on_curve(P):
    if P is O: return True
    x, y = P
    return (y * y - x ** 3 - a * x - b) % p == 0


def add(P, Q):
    if P is O: return Q
    if Q is O: return P
    (x1, y1), (x2, y2) = P, Q

    if x1 == x2 and (y1 + y2) % p == 0:  # P + (-P) = O
        return O
    if P == Q:
        l = (3 * x1 * x1 + a) * pow(2 * y1, -1, p) % p  # tangent: (3x^2 + a) / 2y
    else:
        l = (y2 - y1) * pow(x2 - x1, -1, p) % p  # chord: (y2 - y1) / (x2 - x1)

    x3 = (l * l - x1 - x2) % p
    y3 = (l * (x1 - x3) - y1) % p
    return (x3, y3)


def double(P):
    return add(P, P)


def mul(k, P):
    # double-and-add: kP using bits of k
    R = O
    while k:
        if k & 1: R = add(R, P)
        P = double(P)
        k >>= 1
    return R


P = G
Q = double(G)
print(f"Curve: y^2 = x^3 + {a}x + {b} (mod {p}), G = {G}")
print("P = G   :", P)
print("Q = 2P  :", Q)
print("P + Q   :", add(P, Q))
print("3G == P + Q:", mul(3, G) == add(P, Q))

k = int(input("Enter scalar k: "))
R = mul(k, G)
print(f"{k}G =", R, "| on curve:", on_curve(R))
