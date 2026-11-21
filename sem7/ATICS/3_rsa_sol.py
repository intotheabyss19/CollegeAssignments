# 3. RSA Public-Key Encryption and Decryption


def gcd_ext(a, b):
    if b == 0:
        return a, 1, 0
    g, s1, t1 = gcd_ext(b, a % b)
    s = t1
    t = s1 - a // b * s
    return g, s, t

# p and q between 2^512 and 2^512 (2^1023 and 2^1024)
# e = 2**16 + 1 = 65537

# p = 100000000000031
# q = 100000000100023

# p = 17
# q = 5
# e = 3

p = 61
q = 53
e = 17

n = p * q
phi = (p - 1) * (q - 1)

# Find d ≡ e^−1 (mod phi) or d*e ≡ 1 (mod phi)
_, d, _ = gcd_ext(e, phi)
print(f"n:{n}, phi:{phi}, d:{d}")


def encrypt(m, e, n):
    # c ≡ m^e (mod n)
    c = pow(m, e, n)
    return c


def decrypt(c, d, n):
    # c^d ≡ (m^e)^d ≡ m (mod n)
    p = pow(c, d, n)
    return p

m = int(input("Enter integer message: "))
encrypted = encrypt(m, e, n)
print("Encrypted: ", encrypted)
decrypted = decrypt(encrypted, d, n)
print("Decrypted: ", decrypted)
