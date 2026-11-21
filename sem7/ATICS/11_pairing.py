# 11. Write a program to implement Bilinear Pairing using a algebraic pairing model.

# Model: G1 = Z_q (point aP stored as a·P mod q), GT = subgroup of order q in Z_p*
q = 1019
p = 2 * q + 1  # 2039 (prime)
g = 4          # generator of GT, order q
P = 7          # generator of G1


def e(X, Y):
    # e(aP, bP) = g^(ab) mod p
    return pow(g, X * Y % q, p)


a = int(input("Enter a: "))
b = int(input("Enter b: "))
X, Y = a * P % q, b * P % q
print("aP =", X, " bP =", Y)

print("e(P, P)      =", e(P, P))
print("e(aP, bP)    =", e(X, Y))
print("e(P, P)^(ab) =", pow(e(P, P), a * b, p))

print("\nBilinear      :", e(X, Y) == pow(e(P, P), a * b, p))
print("Additive      :", e((X + Y) % q, P) == e(X, P) * e(Y, P) % p)  # e(X+Y, P) = e(X,P)·e(Y,P)
print("Symmetric     :", e(X, Y) == e(Y, X))
print("Non-degenerate:", e(P, P) != 1)
