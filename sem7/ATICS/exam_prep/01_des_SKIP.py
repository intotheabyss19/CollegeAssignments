"""
=====================================================================
 1. Data Encryption Standard (DES)
=====================================================================
 Install:  pip install pycryptodome      (import naam "Crypto" hai)

>> DES kya hai? (Purpose)
   - DES ek SYMMETRIC BLOCK cipher hai. Symmetric = encrypt aur decrypt dono
     ke liye SAME key. Block = data ko fixed size tukdon (blocks) mein todke
     encrypt karta hai.
   - Block size = 64 bits (8 bytes)
   - Key size   = 64 bits likhte hain, lekin har byte ka 8th bit PARITY bit hai
                  (ignore hota hai) -> EFFECTIVE key = 56 bits
   - IBM ne banaya, 1977 mein US standard (NIST) bana.
   - Aaj INSECURE hai: 2^56 keys brute force se kuch ghanton/dino mein toot jaati
     hain (1998 mein EFF ki "Deep Crack" machine ne 56 ghante mein toda).

>> Algorithm kaise kaam karta hai (andar ka structure)
   DES ek FEISTEL CIPHER hai. Feistel ka idea:
     block ko do halves mein todo: L (left 32 bit), R (right 32 bit)
     har round mein:   L_new = R
                       R_new = L XOR f(R, round_key)
     Magic: decryption ke liye SAME structure, bas round keys ULTE order mein.
     f function ko invertible hone ki zarurat hi nahi!

   Pura flow (64-bit plaintext block):
     1. IP (Initial Permutation)   -> bits ki jagah shuffle
     2. 16 ROUNDS of Feistel, har round mein f(R, K_i):
          a. E (Expansion)  : R ke 32 bits -> 48 bits (kuch bits repeat)
          b. XOR with 48-bit round key K_i
          c. S-BOXES (8 boxes): 48 bits -> 32 bits. Har S-box 6 bit in, 4 bit out.
             Yahi NON-LINEAR part hai = DES ki asli security (confusion).
          d. P (Permutation): 32 bits shuffle (diffusion)
     3. Last round ke baad L aur R swap
     4. FP (Final Permutation) = IP ka inverse -> 64-bit ciphertext

   KEY SCHEDULE (16 round keys kaise bante hain):
     64-bit key -> PC-1 (parity bits hatao) -> 56 bits -> do halves C, D (28-28)
     har round: C, D ko left shift (1 ya 2 bits) -> PC-2 -> 48-bit round key K_i

>> Modes of Operation (library use karte waqt zaroori)
   - ECB (Electronic Code Book): har block alag-alag same key se encrypt.
       Problem: same plaintext block -> same ciphertext block. Pattern dikh jaata
       hai (famous "ECB penguin" image). Use mat karo.
   - CBC (Cipher Block Chaining): har plaintext block ko pehle PICHLE ciphertext
       block se XOR karo, phir encrypt.  C_i = E(P_i XOR C_(i-1))
       Pehle block ke liye random IV (Initialization Vector, 8 bytes DES mein).
       IV secret nahi hota, ciphertext ke saath bhej dete hain.
   - PADDING: message 8 bytes ka multiple nahi hai toh extra bytes jodo.
       PKCS#7: agar 3 bytes kam hain toh 03 03 03 jodo. Decrypt ke baad hata do.

>> Kyun kaam karta hai?
   - Confusion (S-boxes): key aur ciphertext ka relation complex bana dete hain.
   - Diffusion (permutations + 16 rounds): plaintext ka 1 bit badlo toh
     ciphertext ke ~half bits badal jaate hain (AVALANCHE effect).
   - Feistel structure ki wajah se decryption = same algorithm, keys reverse.

>> Kahan use hota tha / hota hai?
   - Purane banking systems, ATM PINs, smart cards.
   - Aaj DES ki jagah AES. Legacy systems mein 3DES (Triple DES) mila jaata hai.
   - 3DES: C = E_K3( D_K2( E_K1(P) ) )  -> effective key 112/168 bits.
     Double DES kaafi nahi kyunki "meet-in-the-middle" attack se sirf 2^57 kaam.

>> Exam trick (yaad rakhne ke liye)
   "new - pad - encrypt - iv"   aur   "new(iv) - decrypt - unpad"
   DES.new(key, DES.MODE_CBC) -> cipher.encrypt(pad(data, 8)) -> cipher.iv
   Key = exactly 8 bytes. Block = 8 bytes.  ("DES = 8, AES = 16")

>> Viva Questions
   Q1. DES ka block size aur key size?
       Ans: Block 64 bits. Key 64 bits jismein 8 parity bits -> effective 56 bits.
   Q2. DES mein kitne rounds?
       Ans: 16 rounds. Har round ki 48-bit sub-key alag hoti hai.
   Q3. Feistel cipher kya hota hai?
       Ans: Block ko L, R halves mein todke L' = R, R' = L XOR f(R, K).
            Decryption same structure se, sirf keys ulte order mein.
   Q4. DES ka sabse important / non-linear part?
       Ans: S-boxes. 8 S-boxes, har ek 6 bits -> 4 bits. Linear nahi hain,
            isliye security inhi se aati hai.
   Q5. Expansion box kya karta hai?
       Ans: R ke 32 bits ko 48 bits bana deta hai taaki 48-bit round key se XOR ho sake.
   Q6. DES ab secure kyun nahi?
       Ans: 56-bit key chhoti hai, brute force (2^56) practical hai.
   Q7. Double DES kyun nahi, Triple DES kyun?
       Ans: Double DES meet-in-the-middle attack se ~2^57 mein toot jaata hai.
            3DES (EDE) se effective security 112 bits.
   Q8. ECB aur CBC mein fark?
       Ans: ECB mein har block independent - same input same output, pattern leak.
            CBC mein har block pichle ciphertext se XOR -> same block alag output.
   Q9. IV kya hai, secret hona chahiye?
       Ans: Initialization Vector - CBC mein first block ke saath XOR hota hai.
            Random hona chahiye, secret nahi.
   Q10. Padding kyun chahiye?
       Ans: Block cipher sirf full 8-byte blocks encrypt karta hai. Message ko
            8 ka multiple banane ke liye padding (PKCS#7) lagate hain.
   Q11. Avalanche effect kya hai?
       Ans: Input ka 1 bit badalne se output ke lagbhag aadhe bits badal jaayein.
"""

from Crypto.Cipher import DES
from Crypto.Util.Padding import pad, unpad
from Crypto.Random import get_random_bytes


# =====================================================================
# PART 1: STEP-BY-STEP SAMJHO (tutorial style - har line explained)
# =====================================================================
print("===== PART 1: DES step by step =====")

# --- Step 1: Key banao ----------------------------------------------
# DES key EXACTLY 8 bytes (64 bits) honi chahiye, warna library error degi.
# Real life mein random key: get_random_bytes(8). Samajhne ke liye fixed.
key = b"secret!!"
print("Step 1: key =", key, "| length =", len(key), "bytes")

# --- Step 2: Message ko bytes mein convert karo ---------------------
# Cipher bytes pe kaam karta hai, string pe nahi. .encode() se str -> bytes.
message = "Hello NIT Sikkim"
data = message.encode("utf-8")
print("Step 2: message bytes =", data, "| length =", len(data))

# --- Step 3: Padding lagao ------------------------------------------
# DES block = 8 bytes. pad() message ko 8 ke multiple tak bhar deta hai.
# 16 bytes already multiple hai -> phir bhi poora ek block (08 x 8) judta hai,
# taaki unpad hamesha jaane kitna hatana hai.
padded = pad(data, DES.block_size)
print("Step 3: padded =", padded.hex(), "| length =", len(padded))

# --- Step 4: Cipher object banao (CBC mode) -------------------------
# MODE_CBC: iv nahi diya toh library khud random 8-byte IV bana deti hai.
cipher = DES.new(key, DES.MODE_CBC)
iv = cipher.iv
print("Step 4: IV (random) =", iv.hex())

# --- Step 5: Encrypt ------------------------------------------------
ciphertext = cipher.encrypt(padded)
print("Step 5: ciphertext =", ciphertext.hex())

# --- Step 6: Decrypt ------------------------------------------------
# Decrypt ke liye NAYA cipher object banana padta hai, SAME key + SAME iv ke saath.
# (Ek cipher object ko encrypt aur decrypt dono ke liye reuse nahi kar sakte.)
decipher = DES.new(key, DES.MODE_CBC, iv=iv)
dec_padded = decipher.decrypt(ciphertext)
print("Step 6: decrypted (padded) =", dec_padded)

# --- Step 7: Padding hatao aur string banao -------------------------
plain = unpad(dec_padded, DES.block_size).decode("utf-8")
print("Step 7: plaintext =", plain, "| match?", plain == message)

# --- Bonus: ECB ki kamzori dekho ------------------------------------
# Do same blocks "AAAAAAAA" + "AAAAAAAA" -> ECB mein dono ka ciphertext SAME.
ecb = DES.new(key, DES.MODE_ECB)
ct = ecb.encrypt(b"AAAAAAAA" * 2)
print("Bonus : ECB block1 =", ct[:8].hex(), " block2 =", ct[8:].hex(), "-> same! pattern leak")


# =====================================================================
# PART 2: EXAM VERSION (bina comments - yahi likhna hai / ratna hai)
# =====================================================================
print("\n===== PART 2: Exam version =====")


def encrypt_des(P, K):
    cipher = DES.new(K, DES.MODE_CBC)
    C = cipher.encrypt(pad(P.encode(), DES.block_size))
    return C, cipher.iv


def decrypt_des(C, K, iv):
    cipher = DES.new(K, DES.MODE_CBC, iv=iv)
    return unpad(cipher.decrypt(C), DES.block_size).decode()


key = get_random_bytes(8)
message = input("Enter a message: ")

C, iv = encrypt_des(message, key)
print("Key       :", key.hex())
print("Encrypted :", C.hex())
print("Decrypted :", decrypt_des(C, key, iv))
