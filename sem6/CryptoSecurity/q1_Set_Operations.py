a = set(map(int, input("Enter Set 1:").split()))
b = set(map(int, input("Enter Set 2:").split()))
print(f"Union: {a | b}\nIntersection: {a & b}\nSubtraction: {a - b}")
