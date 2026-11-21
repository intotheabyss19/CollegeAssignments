"""
Q6. For two given integers a, b where d = gcd(a,b);
∃ two numbers s and t such that as+bt=d.
Write a program to compute s and t using Extended Euclidean Algorithm.
"""

a = 273
b = 98
# s = [0]
# t = [0]


def gcd_ext(a, b):
    if b == 0:
        return a, 1, 0
    g, s1, t1 = gcd_ext(b, a % b)
    s = t1
    t = s1 - a // b * s
    return g, s, t


# def gcd_ext(a, b):
#     if b == 0:
#         return a, 1, 0
#
#     g, x1, y1 = gcd_ext(b, a % b)
#     x = y1
#     y = x - (a // b) * y1
#     return g, x, y


# def gcd_ext(a, b):
#     if (b == 0):
#         return a, 1, 0
#     else:
#         g, s, t = gcd_ext(b, a % b)
#         print(a, b, g, s, t)
#         return g, s, t

g, x, y = gcd_ext(a, b)
print(f"GCD: {g}, s: {x}, t: {y}")
