# WAP to implement Data Encryption Standard (DES) using PyCryptodome

from Crypto.Cipher import DES
from Crypto.Util.Padding import pad, unpad
from Crypto.Random import get_random_bytes


def encrypt_des(P, K):
    cipher = DES.new(K, DES.MODE_CBC)
    padded_text = pad(P.encode('utf-8'), DES.block_size)
    ciphertext = cipher.encrypt(padded_text)
    return ciphertext, cipher.iv


def decrypt_des(C, K, iv):
    cipher = DES.new(K, DES.MODE_CBC, iv=iv)
    decrypted_padded = cipher.decrypt(C)
    plaintext = unpad(decrypted_padded, DES.block_size)
    return plaintext.decode('utf-8')


secret_key = get_random_bytes(8)
message = input("Enter a message: ")

encrypted_msg, message_iv = encrypt_des(message, secret_key)
decrypted_msg = decrypt_des(encrypted_msg, secret_key, message_iv)

print(encrypted_msg)
print(decrypted_msg)
