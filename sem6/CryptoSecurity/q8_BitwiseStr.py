a = "Hello World"


def bit_op(a, val, op):
    return "".join(chr(op(ord(c), val)) for c in a)


for val in (0, 127):
    print(f"With {val}:")
    print(f"\tAND: {bit_op(a, val, int.__and__)}")
    print(f"\tOR: {bit_op(a, val, int.__or__)}")
    print(f"\tXOR: {bit_op(a, val, int.__xor__)}")
