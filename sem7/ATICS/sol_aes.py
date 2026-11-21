# WAP to implement Advanced Encryption Standard (AES) using PyCryptodome

from Crypto.Cipher import AES
from Crypto.Util.Padding import pad, unpad
from Crypto.Random import get_random_bytes


def encrypt_aes(P, K):
    cipher = AES.new(K, AES.MODE_CBC)
    padded_text = pad(P.encode('utf-8'), AES.block_size)
    ciphertext = cipher.encrypt(padded_text)
    return ciphertext, cipher.iv


def decrypt_aes(C, K, iv):
    cipher = AES.new(K, AES.MODE_CBC, iv=iv)
    decrypted_padded = cipher.decrypt(C)
    plaintext = unpad(decrypted_padded, AES.block_size)
    return plaintext.decode('utf-8')


# secret_key = get_random_bytes(32)
# message = input("Enter a message: ")

message = input("Enter a message: ")
secret_key = b"12345678"

encrypted_msg, message_iv = encrypt_aes(message, secret_key)
decrypted_msg = decrypt_aes(encrypted_msg, secret_key, message_iv)

print(encrypted_msg)
print(decrypted_msg)
