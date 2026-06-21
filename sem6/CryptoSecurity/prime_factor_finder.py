n = int(input("Enter an integer: "))
for i in range(2, int(n**0.5) + 1):
    if n % i == 0:
        print(f"Divisible by {i}")
