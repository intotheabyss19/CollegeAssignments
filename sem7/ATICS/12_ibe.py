# 12. Write a program to implement Identity-Based Encryption (IBE) and demonstrate the conceptual IBE workflow: Setup, Extract, Encrypt and Decrypt.

import random
from hashlib import sha256, shake_256

# Pairing model from 11: G1 = Z_q, GT = subgroup of order q in Z_p*
q, p, g, P = 1019, 2039, 4, 7


def e(X, Y):
    return pow(g, X * Y % q, p)


def H1(ID):  # identity -> point in G1
    return int(sha256(ID.encode()).hexdigest(), 16) % (q - 1) + 1


def H2(x, length):  # GT element -> keystream
    return shake_256(str(x).encode()).digest(length)


def xor(a, b):
    return bytes(i ^ j for i, j in zip(a, b))


def setup():
    s = random.randint(1, q - 1)  # master secret key
    return s, s * P % q           # P_pub = sP


def extract(ID, s):
    return s * H1(ID) % q         # d_ID = s·Q_ID


def encrypt(M, ID, P_pub):
    r = random.randint(1, q - 1)
    U = r * P % q
    k = pow(e(H1(ID), P_pub), r, p)  # e(Q_ID, P_pub)^r
    return U, xor(M, H2(k, len(M)))


def decrypt(C, d_ID):
    U, V = C
    k = e(d_ID, U)                   # e(sQ_ID, rP) = e(Q_ID, sP)^r
    return xor(V, H2(k, len(V)))


s, P_pub = setup()
print("Setup  : master key s =", s, " P_pub =", P_pub)

ID = input("Enter receiver's ID: ")
d_ID = extract(ID, s)
print("Extract: Q_ID =", H1(ID), " d_ID =", d_ID)

M = input("Enter message: ").encode()
C = encrypt(M, ID, P_pub)
print("Encrypt: U =", C[0], " V =", C[1].hex())
print("Decrypt:", decrypt(C, d_ID).decode())

d_eve = extract("eve@example.com", s)
print("\nDecrypt with Eve's key:", decrypt(C, d_eve))
