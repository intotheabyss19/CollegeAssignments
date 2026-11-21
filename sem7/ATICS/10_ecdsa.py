# 10. Write a program to implement Elliptic Curve Digital Signature Authentication (ECDSA) algorithm.

import random
from hashlib import sha256

# Curve: y^2 ≡ x^3 + ax + b (mod p), G has prime order n
p, a, b = 10007, 2, 30
G = (1, 283)
n = 10091
O = None


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


def H(m):
    return int(sha256(m.encode()).hexdigest(), 16) % n


def sign(m, d):
    while True:
        k = random.randint(1, n - 1)
        r = mul(k, G)[0] % n
        s = pow(k, -1, n) * (H(m) + d * r) % n
        if r and s: return (r, s)


def verify(m, sig, Q):
    r, s = sig
    if not (0 < r < n and 0 < s < n): return False
    w = pow(s, -1, n)
    u1, u2 = H(m) * w % n, r * w % n
    X = add(mul(u1, G), mul(u2, Q))
    return X is not O and X[0] % n == r


d = random.randint(1, n - 1) # private
Q = mul(d, G) # public
print("Private key d:", d, " Public key Q:", Q)

message = input("Enter a message to sign: ")
sig = sign(message, d)
print("Signature (r, s):", sig)
print("Verified:", verify(message, sig, Q))

tampered = message + "!"
print("\nModified message:", tampered)
print("Verified:", verify(tampered, sig, Q))
