"""
WAP to implement the following substitution and transposition cipher techniques (both encryption and decryption):
- Caesar Cipher as a special case of Affine Cipher
- Vigenere Cipher using Caesar Cipher as a component
- Wheatstone Playfair Cipher
- Polygraphic Hill Cipher
- Rail fence transposition Cipher
"""

# s = "NATIONAL INSTITUTE OF TECHNOLOGY SIKKIM"
s = "NATIONAL SIKKIM"
k = "HELLO WORLD"
# s = "Satya Ranjan"
# k = "Yash"
# s = "HELLO"
# k = "MONARCHY"


# ==========================================
# 1. Affine Cipher (Base Component)
# ==========================================
def affine(ch, a=1, b=0, decrypt=False):
    """Encrypts/Decrypts a single character using Affine cipher math."""
    if not ch.isalpha():
        return ch
    base = 65 if ch.isupper() else 97
    a_inv = pow(a, -1, 26) if decrypt else a
    b_val = -b * a_inv if decrypt else b
    return chr((a_inv * (ord(ch) - base) + b_val) % 26 + base)


# ==========================================
# 2. Caesar Cipher (Uses Affine)
# ==========================================
def caesar(text, shift=3, decrypt=False):
    """Caesar Cipher is a special case of Affine Cipher where a=1."""
    return "".join(affine(ch, 1, shift, decrypt) for ch in text)


# ==========================================
# 3. Vigenere Cipher (Uses Caesar)
# ==========================================
def vigenere(text, key, decrypt=False):
    """Vigenere Cipher cycles through Caesar shifts."""
    shifts = [ord(c.upper()) - 65 for c in key if c.isalpha()]
    res, i = "", 0
    for ch in text:
        if ch.isalpha():
            res += caesar(ch, shifts[i % len(shifts)], decrypt)
            i += 1
        else:
            res += ch
    return res


# ==========================================
# 4. Wheatstone Playfair Cipher
# ==========================================
def playfair(text, key, decrypt=False):
    alpha = "".join(
        dict.fromkeys((key.upper() + "ABCDEFGHIJKLMNOPQRSTUVWXYZ").replace("J", "I"))
    )
    pos = {c: (i // 5, i % 5) for i, c in enumerate(alpha)}
    mat = {v: k for k, v in pos.items()}

    t = "".join(c.upper().replace("J", "I") for c in text if c.isalpha())
    pairs, i = [], 0
    while i < len(t):
        a, b = t[i], t[i + 1] if i + 1 < len(t) else "X"
        if a == b:
            pairs.append((a, "X"))
            i += 1
        else:
            pairs.append((a, b))
            i += 2

    res, d = "", -1 if decrypt else 1
    for a, b in pairs:
        (r1, c1), (r2, c2) = pos[a], pos[b]
        if r1 == r2:
            res += mat[r1, (c1 + d) % 5] + mat[r2, (c2 + d) % 5]
        elif c1 == c2:
            res += mat[(r1 + d) % 5, c1] + mat[(r2 + d) % 5, c2]
        else:
            res += mat[r1, c2] + mat[r2, c1]
    return res


# ==========================================
# 5. Polygraphic Hill Cipher (2x2)
# ==========================================
def hill(text, K, decrypt=False):
    """Hill cipher using a 2x2 matrix."""
    if decrypt:
        inv = pow(K[0][0] * K[1][1] - K[0][1] * K[1][0], -1, 26)
        K = [
            [K[1][1] * inv % 26, -K[0][1] * inv % 26],
            [-K[1][0] * inv % 26, K[0][0] * inv % 26],
        ]

    t = [ord(c.upper()) - 65 for c in text if c.isalpha()]
    if len(t) % 2:
        t.append(23)  # Pad with 'X'

    return "".join(
        chr((K[0][0] * t[i] + K[0][1] * t[i + 1]) % 26 + 65)
        + chr((K[1][0] * t[i] + K[1][1] * t[i + 1]) % 26 + 65)
        for i in range(0, len(t), 2)
    )


# ==========================================
# 6. Rail Fence Transposition Cipher
# ==========================================
def rail_fence(text, rails, decrypt=False):
    """Transposition cipher utilizing a zigzag index cycle mapping."""
    seq = list(range(rails)) + list(range(rails - 2, 0, -1))

    if not decrypt:
        res = [""] * rails
        for i, c in enumerate(text):
            res[seq[i % len(seq)]] += c
        return "".join(res)

    counts = [0] * rails
    for i in range(len(text)):
        counts[seq[i % len(seq)]] += 1

    r_lst, idx = [], 0
    for c in counts:
        r_lst.append(list(text[idx : idx + c]))
        idx += c

    print(r_lst)
    return "".join(r_lst[seq[i % len(seq)]].pop(0) for i in range(len(text)))


# ==========================================
# Execution and Testing
# ==========================================
if __name__ == "__main__":
    print(f"--- ORIGINAL --- \n{s}\n")

    c_enc = caesar(s, 3)
    print(f"[Caesar]   Enc: {c_enc}\n           Dec: {caesar(c_enc, 3, True)}\n")

    v_enc = vigenere(s, k)
    print(f"[Vigenere] Enc: {v_enc}\n           Dec: {vigenere(v_enc, k, True)}\n")

    p_enc = playfair(s, k)
    print(f"[Playfair] Enc: {p_enc}\n           Dec: {playfair(p_enc, k, True)}\n")

    # 2x2 Invertible Key matrix for Hill
    hill_matrix = [[3, 3], [2, 5]]
    h_enc = hill(s, hill_matrix)
    print(
        f"[Hill]     Enc: {h_enc}\n           Dec: {hill(h_enc, hill_matrix, True)}\n"
    )

    r_enc = rail_fence(s, 4)
    print(f"[Rail]     Enc: {r_enc}\n           Dec: {rail_fence(r_enc, 4, True)}\n")
