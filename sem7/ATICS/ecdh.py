import random

p, a, b = 10007, 2, 30
G = (1, 283)
n = 10091
O = None

def add(P, Q):
    if P is O: return Q
    if Q is O: return P

    (x1, y1), (x2, y2) = P, Q
    if x1 == x2 and (y1 + y2) % p == 0: 
        return O
    if P == Q:
        l = (3 * x1 * x1 + a) * pow(2 * y1, -1, p) % p
    else:
        l = (y2 - y1) * pow(x2 - x1, -1, p) % p

    x3 = (l * l - x1 - x2) % p
    return (x3, (l * (x1 - x3) - y1) % p)

def mul(k, P):
    R = O
    while k:
        if k & 1:
            R = add(R, P)
        P = add(P, P)
        k >>= 1
    return R

class User:
    def __init__(self):
        self.private = random.randint(1, n-1)
        self.public = mul(self.private, G)

    def shared_key(self, other_public):
        return mul(self.private, other_public)

A = User()
B = User()
print()

