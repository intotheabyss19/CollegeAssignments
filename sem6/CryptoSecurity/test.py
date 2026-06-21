# Python program to demonstrate working of 
# extended Euclidean Algorithm 

# Function for extended Euclidean Algorithm 
def gcdExtended(a, b, x, y):
    if a == 0: 
        x[0] = 0
        y[0] = 1
        return b 

    x1, y1 = [0], [0]
    gcd = gcdExtended(b % a, a, x1, y1)

    x[0] = y1[0] - (b // a) * x1[0]
    y[0] = x1[0]
    return gcd

def main():
    a, b = 273, 98
    x, y = [1], [1]
    print(gcdExtended(a, b, x, y))
    print(x, y)

if __name__ == "__main__":
    main()
