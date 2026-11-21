# 11. Bilinear Pairing (Algebraic Model)

G1 = Z_q with generator P (point aP stored as a·P mod q),
GT = subgroup of order q in Z_p* with generator g, where q | p − 1

```
PAIRING(X, Y):                           // X = aP, Y = bP
    return g^(X·Y mod q) mod p           // e(aP, bP) = g^(ab)

CHECK_PROPERTIES(a, b):
    X = aP,  Y = bP
    Bilinear      : e(aP, bP) = e(P, P)^(ab)
    Additive      : e(X + Y, P) = e(X, P) · e(Y, P)
    Symmetric     : e(X, Y) = e(Y, X)
    Non-degenerate: e(P, P) ≠ 1
```

# 12. Identity-Based Encryption (Boneh–Franklin)

H1: ID → G1,  H2: GT → keystream,  e = pairing from 11

```
SETUP():                                 // done by the PKG
    s = random in [1, q−1]               // master secret key
    P_pub = s·P                          // master public key
    return s, P_pub

EXTRACT(ID, s):                          // PKG issues the user's private key
    Q_ID = H1(ID)
    d_ID = s·Q_ID
    return d_ID

ENCRYPT(M, ID, P_pub):                   // sender needs only ID and P_pub
    Q_ID = H1(ID)
    r = random in [1, q−1]
    U = r·P
    V = M ⊕ H2( e(Q_ID, P_pub)^r )
    return (U, V)

DECRYPT((U, V), d_ID):
    M = V ⊕ H2( e(d_ID, U) )
    return M
    // e(d_ID, U) = e(s·Q_ID, r·P) = e(Q_ID, s·P)^r
```
