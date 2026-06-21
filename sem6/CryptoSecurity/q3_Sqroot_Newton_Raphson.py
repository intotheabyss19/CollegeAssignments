import time


def sqroot_binary_search(n, prec=5):
    lb = 1
    rb = n
    mid = (lb + rb) / 2
    while abs(n - mid * mid) > 10**-prec:
        mid = (lb + rb) / 2
        if mid * mid == n:
            return mid
        elif mid * mid > n:
            rb = mid
        else:
            lb = mid
    return mid


def sqroot_newton_raphson(n, prec=5):
    x = n
    while abs(n - x * x) > 10**-prec:
        x = 0.5 * (x + n / x)
    return x


def main():
    large = int(input("Enter large integer: "))
    prec = int(input("Enter precision: "))

    warmup = sqroot_binary_search(large, prec)
    start = time.perf_counter()
    print("Binary Search:", sqroot_binary_search(large, prec))
    end = time.perf_counter()
    print(f"Time taken: {end - start}")

    start = time.perf_counter()
    print("Newton Raphson:", sqroot_newton_raphson(large, prec))
    end = time.perf_counter()
    print(f"Time taken: {end - start}")

    start = time.perf_counter()
    print("Num ** 0.5:", large**0.5)
    end = time.perf_counter()
    print(f"Time taken: {end - start}")


if __name__ == "__main__":
    main()
