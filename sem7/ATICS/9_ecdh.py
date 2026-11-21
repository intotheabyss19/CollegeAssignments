# 9. Write a program to implement Elliptic Curve Diffie-Hellman (ECDH) Key agreement algorithm.
"""
```
KEYGEN():
    d = random integer in [1, n−1]       // private key
    Q = d · G                            // public key (scalar multiplication)
    return d, Q

ECDH():
    Alice: (d_A, Q_A) = KEYGEN();  Bob: (d_B, Q_B) = KEYGEN()
    exchange Q_A and Q_B over the public channel
    Alice computes S = d_A · Q_B
    Bob   computes S = d_B · Q_A
    // both equal d_A · d_B · G
```
"""
import random

# Curve: y^2 ≡ x^3 + ax + b (mod p), G has prime order n
p, a, b = 10007, 2, 30
G = (1, 283)
n = 10091
O = None  # point at infinity


def add(P, Q):
    if P is O: return Q
    if Q is O: return P
    (x1, y1), (x2, y2) = P, Q
    if x1 == x2 and (y1 + y2) % p == 0: return O
    if P == Q: l = (3 * x1 * x1 + a) * pow(2 * y1, -1, p) % p
    else: l = (y2 - y1) * pow(x2 - x1, -1, p) % p
    x3 = (l * l - x1 - x2) % p
    return (x3, (l * (x1 - x3) - y1) % p)


def mul(k, P):
    R = O
    while k:
        if k & 1: R = add(R, P)
        P = add(P, P)
        k >>= 1
    return R


class User:
    def __init__(self):
        self.private = random.randint(1, n - 1)  # d
        self.public = mul(self.private, G)       # Q = dG

    def shared_key(self, other_public):
        # S = d_A * Q_B = d_A * d_B * G = d_B * Q_A
        return mul(self.private, other_public)


A = User()
B = User()
print(f"Curve: y^2 = x^3 + {a}x + {b} (mod {p}), G = {G}, n = {n}")
print("Alice: d_A =", A.private, " Q_A =", A.public)
print("Bob  : d_B =", B.private, " Q_B =", B.public)

S_A = A.shared_key(B.public)
S_B = B.shared_key(A.public)
print("Alice's shared key:", S_A)
print("Bob's shared key  :", S_B)
print("Keys match:", S_A == S_B)
