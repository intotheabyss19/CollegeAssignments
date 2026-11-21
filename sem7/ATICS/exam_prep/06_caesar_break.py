"""
=====================================================================
 6. Breaking the Mono-alphabetic Cipher (Caesar assume karke)
=====================================================================

>> Mono-alphabetic cipher kya hai? (Purpose)
   - "Mono" = ek. Poore message mein har letter ka SAME replacement hota hai.
     Agar A -> D bana, toh message mein har jagah A -> D hi banega.
   - Sabse simple mono-alphabetic cipher = CAESAR CIPHER: har letter ko k
     positions aage shift karo (k = key, 0..25).
       k = 3:  HELLO -> KHOOR      (H+3=K, E+3=H, L+3=O, O+3=R)
   - Lab mein sir ka rule: mono-alphabetic ko CAESAR maan ke todna hai.
     (General substitution ke liye bonus file dekho: 06b_mono_general_BONUS.py)

>> Algorithm
   Encrypt:  C = (P + k) mod 26
   Decrypt:  P = (C - k) mod 26        (letters ko number maan ke: A=0 ... Z=25)

   BREAK ("lock" tareeka - lab mein yahi dikhaya, sir ne OK kiya):
     1. User ek word deta hai -> program use random key se LOCK (encrypt) karta hai.
     2. Attacker ko sirf ciphertext dikhta hai. Woh k = 0, 1, 2, ... 25 try karta hai
        (BRUTE FORCE - Caesar mein sirf 26 keys hain).
     3. Har attempt: decrypt(C, k) ko original word se match karo.
          match nahi  -> "Match didn't occur", agla k
          match hua   -> "Success!", key = k, loop ROKO (break)

>> Haath se chhota example
   Word = "HELLO", random key = 3  ->  locked = "KHOOR"
   k = 0 -> KHOOR   Match didn't occur
   k = 1 -> JGNNQ   Match didn't occur
   k = 2 -> IFMMP   Match didn't occur
   k = 3 -> HELLO   Success! key = 3   (yahin ruk gaye)

>> Agar original word pata NA ho? (sirf ciphertext ho)
   Tab match karne ko kuch nahi hai -> FREQUENCY ANALYSIS:
     har k ke decrypted text ke letter counts ko English ke normal % se compare
     karo (chi-squared). Jiska chi^2 sabse kam -> wahi English jaisa -> wahi key.
       chi^2 = SUM (observed - expected)^2 / expected,  expected = N * FREQ[letter] / 100
   Yeh bilkul wahi chi_sq function hai jo Exp 7 (Vigenere) mein hai - Vigenere ka har
   column ek Caesar cipher hi hai! Shortcut: lambe text mein sabse common letter = E.
   (Chhote text, jaise "HELLO WORLD", pe frequency analysis galat bhi ho sakta hai.)

>> Agar Caesar assume NA kar sakein (general substitution)?
   - Key = alphabet ka koi bhi arrangement -> 26! ≈ 4 * 10^26 keys -> brute force IMPOSSIBLE.
   - Tareeka: (1) frequency analysis se pehla guess (cipher ka sabse common letter -> E,
     doosra -> T ... "ETAOIN SHRDLU" order), (2) phir HILL CLIMBING: key ke do letters swap
     karo, agar text zyada English jaisa lage (common bigrams TH, HE, IN... / trigrams THE,
     AND, ING ka score badhe) toh swap rakho, warna chhod do. Hazaaron baar repeat.
   - Code: 06b_mono_general_BONUS.py

>> Kyun kaam karta hai?
   - Caesar ka key space sirf 26 hai -> computer saari keys ek pal mein try kar leta hai.
   - Sahi key pe decrypt karne se original word hi wapas aata hai, isliye match = sahi key.

>> Kahan use hota hai?
   - Real security mein KAHIN NAHI (bahut weak). History: Julius Caesar ne use kiya.
   - ROT13 (k = 13) forums pe spoilers chhupane ke liye.
   - Concept important hai: Vigenere (Exp 7) ka har column ek Caesar cipher hai.

>> Exam trick (yaad rakhne ke liye)
   "word lo -> random key se lock -> k = 0..25 try -> match pe Success + break"
   shift(text, k) ek hi function: encrypt = shift(+k), decrypt = shift(-k).

>> Viva Questions
   Q1. Mono-alphabetic aur poly-alphabetic mein kya fark hai?
       Ans: Mono: har letter ka ek fixed replacement (Caesar, substitution).
            Poly: same letter alag positions pe alag ban sakta hai (Vigenere) - key repeat hoti hai.
   Q2. Caesar cipher ka key space kitna hai?
       Ans: 26 (0..25), useful sirf 25 (k = 0 matlab koi encryption nahi).
   Q3. General substitution cipher ka key space?
       Ans: 26! ≈ 4 * 10^26 - brute force possible nahi, frequency analysis se todte hain.
   Q4. Brute force attack kya hai?
       Ans: Har possible key try karna. Caesar mein sirf 26 -> turant toot jaata hai.
   Q5. Aapke program mein sahi key kaise pehchani?
       Ans: Har attempt ko original word se compare kiya - match hote hi Success aur loop break.
            (Yeh "known-plaintext" check hai - attacker ko pata hai message kya ho sakta hai.)
   Q6. Agar original word pata na ho toh?
       Ans: Frequency analysis (chi-squared) - jo shift sabse English jaisa text de woh key.
   Q7. Frequency analysis kisne invent kiya? English ke common letters?
       Ans: Al-Kindi (9th century). E T A O I N S H R D L U ("ETAOIN SHRDLU").
   Q8. Known-plaintext attack kya hai?
       Ans: Attacker ke paas kuch (plaintext, ciphertext) pairs hain, unse key nikalta hai.
            Caesar mein ek hi letter pair kaafi hai: k = (C - P) mod 26.
   Q9. Caesar ko strong kaise bana sakte hain?
       Ans: Nahi bana sakte - key space hi chhota hai. Isliye poly-alphabetic (Vigenere)
            aaye, aur aaj modern ciphers (AES).
   Q10. ROT13 kya hai?
       Ans: Caesar with k = 13. Do baar lagao toh original wapas (13 + 13 = 26 ≡ 0).
   Q11. Kya Caesar sirf letters pe kaam karta hai?
       Ans: Haan, numbers/spaces/punctuation waise hi rehte hain - yeh bhi ek kamzori hai
            (words ki length aur spaces dikh jaate hain).
"""


# =====================================================================
# PART 1: CODE SAMJHO (Part 2 wala code + har line ka manual)
# =====================================================================
# Neeche bilkul wahi code hai jo PART 2 mein hai, bas har line ke saath
# explanation. Sirf ek farak: input() ki jagah fixed value di hai (taaki
# file chalane pe do baar input na maange). Asli input() line comment mein hai.
print("===== PART 1: Annotated version =====")

# random module (built-in): random numbers ke liye.
#   random.randint(a, b) -> a se b ke beech ka random integer, DONO ends included.
#   randint(1, 25) -> 1..25 (0 nahi liya kyunki k = 0 matlab koi encryption hi nahi).
import random

# Alphabet string. A.index('D') = 3 -> letter ko number banata hai,
# A[3] = 'D' -> number ko wapas letter banata hai.
A = 'ABCDEFGHIJKLMNOPQRSTUVWXYZ'


# --- shift(): encrypt aur decrypt dono -----------------------------------
# k positive -> encrypt (aage khiskao), k negative -> decrypt (peeche khiskao).
def shift(text, k):
    # Har character c ke liye:
    #   agar letter hai: A.index(c) se number (0..25), + k, % 26 (Z ke baad wapas A),
    #                    phir A[...] se wapas letter.  Example: 'Y' + 3 -> (24+3)%26 = 1 -> 'B'
    #   warna (space, comma, digit): waise hi rakh do.
    # Python mein (-1) % 26 = 25 hota hai (positive), isliye decrypt (k negative) bhi seedha chalta hai.
    # ''.join(...) saare characters jod ke ek string bana deta hai.
    return ''.join(A[(A.index(c) + k) % 26] if c in A else c for c in text)


# word = input("Enter word to lock: ").upper()
#   input() string deta hai. .upper() -> sab capital (A mein sirf capital letters hain,
#   'hello' -> 'HELLO').
word = "HELLO"

# Edge case: agar word mein ek bhi letter nahi (empty, ya "123") toh Caesar kuch
# change hi nahi karega -> k = 0 pe hi "match" ho jaayega. Isliye dobara maango.
#   any(...) -> agar koi bhi ek item True ho toh True. Yahan: "kya koi letter hai?"
#   while ... : jab tak letter na mile, input maangte raho.
while not any(c in A for c in word):
    # word = input("Need at least one letter: ").upper()
    word = "HELLO"

# LOCK: random key se encrypt. Attacker ko yeh key nahi pata.
key = random.randint(1, 25)
C = shift(word, key)
print("Locked (ciphertext):", C)

# BREAK: brute force - har possible key k = 0..25 try karo.
for k in range(26):                    # range(26) = 0, 1, ..., 25
    attempt = shift(C, -k)             # k maan ke decrypt karo (peeche khiskao)
    # {k:2d} = number ko 2 jagah mein right-align (sirf output seedha dikhne ke liye)
    if attempt == word:                # original word se match? -> sahi key mil gayi
        print(f"k = {k:2d}: {attempt} -> Success! Key found =", k)
        break                          # break = loop turant band, aage ke k try nahi honge
    print(f"k = {k:2d}: {attempt} -> Match didn't occur")


# =====================================================================
# PART 2: EXAM VERSION (bina comments - yahi likhna hai / ratna hai)
# =====================================================================
print("\n===== PART 2: Exam version =====")

import random

A = 'ABCDEFGHIJKLMNOPQRSTUVWXYZ'


def shift(text, k):
    return ''.join(A[(A.index(c) + k) % 26] if c in A else c for c in text)


word = input("Enter word to lock: ").upper()
while not any(c in A for c in word):
    word = input("Need at least one letter: ").upper()

key = random.randint(1, 25)
C = shift(word, key)
print("Locked (ciphertext):", C)

for k in range(26):
    attempt = shift(C, -k)
    if attempt == word:
        print(f"k = {k:2d}: {attempt} -> Success! Key found =", k)
        break
    print(f"k = {k:2d}: {attempt} -> Match didn't occur")
