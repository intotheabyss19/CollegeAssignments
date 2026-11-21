# WAP to implement Data Encryption Standard (DES)

def hex2bin(h):
    return bin(int(h, 16))[2:].zfill(len(h)*4)

def bin2hex(b):
    return hex(int(b, 2))[2:]

def xor(a, b):
    ''' a, b are binary '''
    x = []
    for i in range(len(a)):
        if a[i] == b[i]:
            x.append('0')
        else: x.append('1')
    return ''.join(x)

def permute(bits, table):

