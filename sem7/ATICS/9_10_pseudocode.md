# 9. Elliptic Curve Diffie-Hellman (ECDH)

Public: curve (p, a, b), base point G of prime order n

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

# 10. Elliptic Curve Digital Signature Algorithm (ECDSA)

Keys: private d ∈ [1, n−1], public Q = d · G

```
SIGN(m, d):
    e = HASH(m) mod n
    repeat:
        k = random integer in [1, n−1]
        r = (k · G).x mod n
        s = k⁻¹ (e + d·r) mod n
    until r ≠ 0 and s ≠ 0
    return (r, s)

VERIFY(m, (r, s), Q):
    if r, s not in [1, n−1]: return INVALID
    e = HASH(m) mod n
    w = s⁻¹ mod n
    u1 = e·w mod n,  u2 = r·w mod n
    X = u1·G + u2·Q
    if X ≠ O and X.x mod n = r: return VALID
    else return INVALID
```
