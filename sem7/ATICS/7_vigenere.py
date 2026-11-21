# 7. Write a program to break a Vigenère (poly alphabetic) cipher using frequency analysis and key-length estimation

A = 'ABCDEFGHIJKLMNOPQRSTUVWXYZ'
# English letter frequencies (%) for A..Z
FREQ = [8.2, 1.5, 2.8, 4.3, 12.7, 2.2, 2.0, 6.1, 7.0, 0.2, 0.8, 4.0, 2.4,
        6.7, 7.5, 1.9, 0.1, 6.0, 6.3, 9.1, 2.8, 1.0, 2.4, 0.2, 2.0, 0.1]


def vigenere(text, key, sign=1):
    # C_i = (P_i + K_(i mod m)) mod 26, sign = -1 for decryption
    return ''.join(A[(A.index(c) + sign * A.index(key[i % len(key)])) % 26]
                   for i, c in enumerate(text))


def ic(s):
    # Index of Coincidence = sum f(f-1) / N(N-1), English ~ 0.066, random ~ 0.038
    N = len(s)
    return sum(s.count(c) * (s.count(c) - 1) for c in A) / (N * (N - 1))


def key_length(c, max_len=12):
    # split into m columns, each column is a Caesar cipher -> high IC if m is right
    ics = [sum(ic(c[i::m]) for i in range(m)) / m for m in range(1, max_len + 1)]
    # multiples of m also score high, so take the smallest m close to the best
    return next(m for m, v in enumerate(ics, 1) if v >= 0.9 * max(ics))


def chi_sq(s):
    N = len(s)
    return sum((s.count(A[i]) - N * FREQ[i] / 100) ** 2 / (N * FREQ[i] / 100) for i in range(26))


def crack(c):
    m = key_length(c)
    # for each column try all 26 shifts, keep the one closest to English
    key = ''.join(A[min(range(26), key=lambda k: chi_sq(vigenere(c[i::m], A[k], -1)))]
                  for i in range(m))
    return key, vigenere(c, key, -1)


text = """Cryptography is the practice of securing communication in the presence of
adversaries. A classical cipher such as the Vigenere cipher uses a repeating keyword
to shift each letter of the message by a different amount. For a long time it was
believed to be unbreakable, but the repetition of the key leaves patterns in the
ciphertext. Once the length of the key is known, the message splits into several
simple shift ciphers, and each of them can be solved by comparing its letter counts
with the normal frequencies of the English language."""

P = ''.join(ch for ch in text.upper() if ch in A)
key = input("Enter key: ").upper()

C = vigenere(P, key)
print("Ciphertext:", C)

found_key, plain = crack(C)
print("Key length:", len(found_key))
print("Found key :", found_key)
print("Plaintext :", plain)
