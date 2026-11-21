# 3. RSA Public-Key Encryption and Decryption


def gcd_ext(a, b):
    if b == 0:
        return a, 1, 0
    g, s1, t1 = gcd_ext(b, a % b)
    s = t1
    t = s1 - a // b * s
    return g, s, t


class Alice:
    def __init__(self, p, q, e):
        self.p = p
        self.q = q
        self.e = e
        self.n = p * q
        self.phi = (p - 1) * (q - 1)

        _, self.d, _ = gcd_ext(e, self.phi)

        self.public = (self.e, self.n)
        self.private = (self.d, self.n)

    def decrypt(self, c):
        p = pow(c, self.private[0], self.private[1])
        return p


class Bob:
    def __init__(self, m):
        self.m = m

    def encrypt(self, pub):
        c = pow(self.m, pub[0], pub[1])
        return c

p = 100000000000031
q = 100000000100023
e = 65537
A = Alice(p, q, e)

m = int(input("Enter integer message: "))
B = Bob(m)

encrypted = B.encrypt(A.public)
print("Encrypted: ", encrypted)

decrypted = A.decrypt(encrypted)
print("Decrypted: ", decrypted)
