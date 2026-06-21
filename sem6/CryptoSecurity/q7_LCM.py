"""
WAP to calculate LCM of two large numbers using:
1. Prime Factorization
2. GCD method
"""

from q4_isPrime_Miller_Rabin import isPrime
from q5_GCD_Euclidean import gcd
from collections import defaultdict


def find_next_prime(n):
    """If takes a prime number bigger than 2 and returns the succeeding prime"""
    if n <= 2:
        return 3
    while isPrime(n + 2) == 0:
        n += 2
    return n + 2


def factorize(n):
    factors = defaultdict(int)
    prime = 2
    while n != 1:
        if n % prime == 0:
            n /= prime
            factors[prime] += 1
        else:
            prime = find_next_prime(prime)
    return factors


def lcm_pf(a, b):
    fac_a = factorize(a)
    fac_b = factorize(b)
    fac = {
        key: max(fac_a.get(key, float("-inf")), fac_b.get(key, float("-inf")))
        for key in fac_a.keys() | fac_b.keys()
    }
    lcm = 1
    for key in fac.keys():
        lcm *= key ** fac[key]
    return lcm


def lcm_gcd(a, b):
    return a // gcd(a, b) * b


if __name__ == "__main__":
    a = int(input("Enter large a: "))
    b = int(input("Enter large b: "))
    print("LCM \nUsing Prime Factorization:", lcm_pf(a, b))
    print("Using GCD:", lcm_gcd(a, b))
