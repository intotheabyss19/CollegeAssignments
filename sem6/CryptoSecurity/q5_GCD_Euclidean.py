# WAP to find GCD of two large integers using Euclidean Algorithm.


# gcd = lambda a, b: gcd(b, a % b) if b else a
def gcd(a, b):
    while b:
        a, b = b, a % b
    return a


if __name__ == "__main__":
    large_a = int(input("Enter a: "))
    large_b = int(input("Enter b: "))
    print(f"GCD of {large_a}, {large_b} is : {gcd(large_a, large_b)}")
