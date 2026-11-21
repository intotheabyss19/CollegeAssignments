"""
=====================================================================
 2. Advanced Encryption Standard (AES)
=====================================================================
 Install:  pip install pycryptodome      (import naam "Crypto" hai)

>> AES kya hai? (Purpose)
   - AES bhi DES ki tarah SYMMETRIC BLOCK cipher hai (same key dono taraf),
     lekin DES ka secure replacement. 2001 mein NIST standard bana.
   - Asli naam: RIJNDAEL (Belgian cryptographers Daemen aur Rijmen).
   - Block size = 128 bits (16 bytes)  -> HAMESHA fixed
   - Key size   = 128 / 192 / 256 bits (16 / 24 / 32 bytes)
   - Rounds     = 10 / 12 / 14  (key size ke hisaab se)
   - Aaj bhi secure hai. Koi practical attack nahi, brute force 2^128 impossible.

>> Algorithm kaise kaam karta hai (andar ka structure)
   AES Feistel NAHI hai. Yeh SPN (Substitution-Permutation Network) hai -
   har round mein POORA block badalta hai (DES mein sirf half).
   16 bytes ko 4x4 matrix ("STATE") mein rakhte hain (column-wise).

   Flow (AES-128):
     0. AddRoundKey (initial)      -> state XOR key
     1. Rounds 1 se 9, har round mein 4 steps:
          a. SubBytes   : har byte S-box se replace (non-linear -> CONFUSION)
          b. ShiftRows  : row 0 same, row 1 ko 1 left, row 2 ko 2, row 3 ko 3 rotate
          c. MixColumns : har column ko fixed matrix se multiply (GF(2^8) mein)
                          -> ek byte ka asar poore column pe (DIFFUSION)
          d. AddRoundKey: state XOR round key
     2. Round 10 (LAST): SubBytes, ShiftRows, AddRoundKey -> MixColumns NAHI hota
   Yaad: "Sub - Shift - Mix - Add", last round mein Mix gayab.

   KEY EXPANSION: 16-byte key se 11 round keys (initial + 10) banti hain,
   RotWord, SubWord aur Rcon (round constant) use karke.

   Decryption: saare steps ke INVERSE ulte order mein
   (InvShiftRows, InvSubBytes, AddRoundKey, InvMixColumns).

>> Modes of Operation, IV, Padding
   - ECB: har 16-byte block alag encrypt -> same block same output, pattern leak.
   - CBC: C_i = E(P_i XOR C_(i-1)), pehle block ke liye random 16-byte IV.
   - (Aur bhi: CTR, GCM - GCM aaj HTTPS mein sabse common, encryption + integrity)
   - PADDING (PKCS#7): message ko 16 ka multiple banao, jaise 5 kam -> 05 05 05 05 05

>> Kyun kaam karta hai?
   - SubBytes non-linear hai (GF(2^8) mein inverse + affine transform).
   - ShiftRows + MixColumns: 2 rounds mein hi har output byte, har input byte
     pe depend karne lagta hai (full diffusion / avalanche).
   - Har round mein alag round key -> key ka asar har jagah.

>> Kahan use hota hai?
   - Har jagah! HTTPS/TLS (AES-GCM), WiFi WPA2/WPA3, BitLocker, FileVault,
     WhatsApp/Signal, VPNs, ZIP/7z password protection.
   - Modern CPUs mein AES-NI instructions -> hardware mein bahut fast.

>> Exam trick (yaad rakhne ke liye)
   Code bilkul DES jaisa hai, bas "DES" ki jagah "AES" aur key 16 bytes.
   "DES = 8, AES = 16"  (block size bytes mein)
   Key = 16/24/32 bytes, warna "Incorrect AES key length" error.

>> Viva Questions
   Q1. AES ka block size aur key sizes?
       Ans: Block 128 bits fixed. Key 128, 192 ya 256 bits.
   Q2. Rounds kitne?
       Ans: 10 (128-bit), 12 (192-bit), 14 (256-bit key).
   Q3. AES ke 4 round steps?
       Ans: SubBytes, ShiftRows, MixColumns, AddRoundKey.
   Q4. Last round mein kya alag hai?
       Ans: MixColumns nahi hota.
   Q5. AES Feistel hai?
       Ans: Nahi, SPN (Substitution-Permutation Network) hai. Poora block har round badalta hai.
   Q6. Confusion aur diffusion kaun deta hai?
       Ans: Confusion = SubBytes (S-box). Diffusion = ShiftRows + MixColumns.
   Q7. AES ki arithmetic kis field mein hoti hai?
       Ans: Galois Field GF(2^8), irreducible polynomial x^8 + x^4 + x^3 + x + 1.
   Q8. DES vs AES?
       Ans: DES: 64-bit block, 56-bit key, 16 rounds, Feistel, insecure.
            AES: 128-bit block, 128/192/256 key, 10/12/14 rounds, SPN, secure.
   Q9. CBC mein IV kyun?
       Ans: Taaki same message do baar encrypt karne pe alag ciphertext aaye.
            Random hona chahiye, secret nahi.
   Q10. Padding kya hai?
       Ans: Message ko 16 bytes ke multiple tak bharna (PKCS#7), decrypt ke baad hatana.
   Q11. AES ka original naam?
       Ans: Rijndael.
"""

from Crypto.Cipher import AES
from Crypto.Util.Padding import pad, unpad
from Crypto.Random import get_random_bytes


# =====================================================================
# PART 1: STEP-BY-STEP SAMJHO (tutorial style - har line explained)
# =====================================================================
print("===== PART 1: AES step by step =====")

# --- Step 1: Key banao ----------------------------------------------
# AES-128 ke liye key EXACTLY 16 bytes. (24 -> AES-192, 32 -> AES-256)
# Real life mein: get_random_bytes(16). Samajhne ke liye fixed key.
key = b"thisis16bytekey!"
print("Step 1: key =", key, "| length =", len(key), "bytes -> AES-128, 10 rounds")

# --- Step 2: Message ko bytes mein convert karo ---------------------
message = "Hello NIT Sikkim"
data = message.encode("utf-8")
print("Step 2: message bytes =", data, "| length =", len(data))

# --- Step 3: Padding lagao ------------------------------------------
# AES block = 16 bytes. Hamara message exactly 16 hai, phir bhi pad() ek pura
# extra block (10 x 16, hex mein "10" = 16) jodega -> 32 bytes.
padded = pad(data, AES.block_size)
print("Step 3: padded =", padded.hex(), "| length =", len(padded))

# --- Step 4: Cipher object banao (CBC mode) -------------------------
# IV nahi diya toh library random 16-byte IV bana deti hai.
cipher = AES.new(key, AES.MODE_CBC)
iv = cipher.iv
print("Step 4: IV (random) =", iv.hex())

# --- Step 5: Encrypt ------------------------------------------------
# Andar har 16-byte block pe 10 rounds of Sub-Shift-Mix-Add chal rahe hain.
ciphertext = cipher.encrypt(padded)
print("Step 5: ciphertext =", ciphertext.hex())

# --- Step 6: Decrypt ------------------------------------------------
# Naya cipher object, SAME key + SAME iv. Encrypt wala object reuse nahi hota.
decipher = AES.new(key, AES.MODE_CBC, iv=iv)
dec_padded = decipher.decrypt(ciphertext)
print("Step 6: decrypted (padded) =", dec_padded)

# --- Step 7: Padding hatao aur string banao -------------------------
plain = unpad(dec_padded, AES.block_size).decode("utf-8")
print("Step 7: plaintext =", plain, "| match?", plain == message)

# --- Bonus: CBC mein same message, naya IV -> alag ciphertext --------
c2 = AES.new(key, AES.MODE_CBC).encrypt(padded)
print("Bonus : same message, naya IV ->", c2.hex()[:32], "... (pehle se alag)")


# =====================================================================
# PART 2: EXAM VERSION (bina comments - yahi likhna hai / ratna hai)
# =====================================================================
print("\n===== PART 2: Exam version =====")


def encrypt_aes(P, K):
    cipher = AES.new(K, AES.MODE_CBC)
    C = cipher.encrypt(pad(P.encode(), AES.block_size))
    return C, cipher.iv


def decrypt_aes(C, K, iv):
    cipher = AES.new(K, AES.MODE_CBC, iv=iv)
    return unpad(cipher.decrypt(C), AES.block_size).decode()


key = get_random_bytes(16)
message = input("Enter a message: ")

C, iv = encrypt_aes(message, key)
print("Key       :", key.hex())
print("Encrypted :", C.hex())
print("Decrypted :", decrypt_aes(C, key, iv))
