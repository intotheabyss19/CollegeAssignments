# 7. Breaking the Vigenère Cipher

```
IC(S):                                   // Index of Coincidence
    return Σ f_c (f_c − 1) / N (N − 1)   // English ≈ 0.066, random ≈ 0.038

KEY_LENGTH(C, maxLen):
    for m = 1 to maxLen:
        split C into m columns: col_i = C[i], C[i+m], C[i+2m], ...
        avgIC[m] = average of IC(col_i) over all columns
    return smallest m with avgIC[m] ≥ 0.9 × max(avgIC)

CRACK(C):
    m = KEY_LENGTH(C)
    for i = 0 to m−1:
        col = C[i], C[i+m], ...
        for k = 0 to 25:
            D = col shifted back by k
            χ²[k] = Σ (count(D, ch) − N·freq(ch))² / (N·freq(ch))
        key[i] = letter k with minimum χ²[k]
    P[j] = (C[j] − key[j mod m]) mod 26
    return key, P
```

# 8. Elliptic-Curve Arithmetic over a Prime Field

Curve: y² ≡ x³ + ax + b (mod p), O = point at infinity

```
ADD(P, Q):
    if P = O return Q;  if Q = O return P
    if x1 = x2 and y1 + y2 ≡ 0 (mod p): return O         // P + (−P)
    if P = Q:  λ = (3x1² + a) · (2y1)⁻¹ mod p            // doubling
    else:      λ = (y2 − y1) · (x2 − x1)⁻¹ mod p         // addition
    x3 = λ² − x1 − x2 mod p
    y3 = λ(x1 − x3) − y1 mod p
    return (x3, y3)

SCALAR_MUL(k, P):                                        // double-and-add
    R = O
    while k > 0:
        if k is odd: R = ADD(R, P)
        P = ADD(P, P)
        k = k >> 1
    return R
```
