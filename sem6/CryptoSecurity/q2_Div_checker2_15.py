large = int(input("Enter integer: "))
for p in range(2, 16):
    if large % p == 0:
        print(f"Large number divisible by: {p}")
