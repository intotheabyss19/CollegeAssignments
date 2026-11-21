# 4. Generate and verify a digital signature and demonstrate rejection of a modified message using RSA-PSS (Probabilistic Signature Scheme).

from sympy import gcd, mod_inverse, randprime

from cryptography.exceptions import InvalidSignature
from cryptography.hazmat.primitives import hashes
from cryptography.hazmat.primitives.asymmetric import padding, rsa

PSS = padding.PSS(mgf=padding.MGF1(hashes.SHA256()),
                  salt_length=padding.PSS.MAX_LENGTH)


def keygen(bits=1024, e=65537):
    # p, q picked with sympy; bits is the size of each prime.
    while True:
        p = randprime(2 ** (bits - 1), 2 ** bits)
        q = randprime(2 ** (bits - 1), 2 ** bits)
        if p != q and gcd(e, (p - 1) * (q - 1)) == 1:
            break

    if p < q: p, q = q, p  # so that qInv = q^-1 mod p 

    n = p * q
    d = mod_inverse(e, (p - 1) * (q - 1))  # d = e^-1 (mod phi)

    return rsa.RSAPrivateNumbers(
        p=p, q=q, d=d,
        dmp1=d % (p - 1),
        dmq1=d % (q - 1),
        iqmp=mod_inverse(q, p),
        public_numbers=rsa.RSAPublicNumbers(e=e, n=n),
    ).private_key()


class Alice:
    def __init__(self):
        self.private_key = keygen()
        self.public = self.private_key.public_key()

    def sign(self, m):
        return self.private_key.sign(m, PSS, hashes.SHA256())


class Bob:
    def __init__(self, pub):
        self.pub = pub

    def verify(self, m, signature):
        try:
            self.pub.verify(signature, m, PSS, hashes.SHA256())
            return True
        except InvalidSignature:
            return False


A = Alice()
B = Bob(A.public)

message = input("Enter a message to sign: ").encode()
signature = A.sign(message)

print("Signature:", signature.hex())
print("Verified :", B.verify(message, signature))

tampered = message + b"!"
print("\nModified message:", tampered.decode())
print("Verified :", B.verify(tampered, signature))
