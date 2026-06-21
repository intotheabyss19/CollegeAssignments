from q3_Sqroot_Newton_Raphson import sqroot_newton_raphson


def isPrime(n):
    if n < 2:
        return 0
    for i in range(2, int(sqroot_newton_raphson(n) + 1)):
        if n % i == 0:
            return 0
    return 1


def isPrime_miller_rabin(n, k=5):
    # if n is even then don't run
    if n % 2 == 0:
        return 0
    d = n - 1
    s = 0
    # Find d
    while d % 2 == 0:
        d /= 2
        s += 1
        print(f"d: {d}, s: {s}")


if __name__ == "__main__":
    large = int(input("Enter a number: "))
    # large = 49
    print("isPrime: ", isPrime_miller_rabin(large))
    print("isPrime: ", isPrime(large))
