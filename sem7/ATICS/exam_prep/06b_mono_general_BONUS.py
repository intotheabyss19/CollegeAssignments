"""
>>> BONUS FILE (exam ke liye NAHI) <<<
   Lab mein sir ne bola: mono-alphabetic ko CAESAR maan ke todo -> woh 06_caesar_break.py hai.
   Yeh file GENERAL substitution cipher (koi bhi random 26-letter key) todti hai -
   sirf samajhne / viva ke liye: "agar Caesar assume na kar sakein toh kya karoge?"

=====================================================================
 6. Breaking the Mono-alphabetic (Substitution) Cipher
=====================================================================

>> Mono-alphabetic cipher kya hai? (Purpose)
   - Har plaintext letter ko HAMESHA ek fixed doosre letter se replace karte hain.
     Key = alphabet ka ek shuffle (permutation), jaise:
         Plain : ABCDEFGHIJKLMNOPQRSTUVWXYZ
         Cipher: QWERTYUIOPASDFGHJKLZXCVBNM      (A->Q, B->W, C->E ...)
     "HELLO" -> "ITSSG"   (dono L -> S, kyunki mapping fixed hai)
   - Caesar cipher iska special case hai (shuffle ki jagah sirf shift).
   - Is experiment ka kaam: KEY PATA NAHI, sirf ciphertext hai -> plaintext nikalo.

>> Brute force kyun kaam nahi karta?
   - Possible keys = 26! ≈ 4 x 10^26 (~2^88). Har second 10^9 keys try karo,
     tab bhi ~10^10 saal lagenge.
   - Lekin cipher phir bhi weak hai, kyunki letter FREQUENCY chhupti nahi.

>> Algorithm: Frequency Analysis + Hill Climbing
   1. FREQUENCY ANALYSIS (pehla guess):
      English mein letters ka order (sabse common se kam):
          E T A O I N S H R D L C U M W F G Y P B V K J X Q Z   ("ETAOIN SHRDLU")
      Ciphertext ke letters ko frequency se sort karo -> sabse common cipher
      letter = E, doosra = T, ... -> yeh pehli key guess hai (~50-70% sahi).
   2. SCORING (kitna "English jaisa" hai):
      Ek English reference text lo, usme har 1, 2, 3 letter ke tukde (n-grams,
      jaise "TH", "THE", "ING") ki count banao. Decrypted text ka score =
      sum of log(count + 1) of uske saare n-grams. Zyada English-like -> zyada score.
   3. HILL CLIMBING (guess sudharo):
      Key mein 2 random letters swap karo -> score check karo.
      Score badha (ya same raha) toh nayi key rakho, warna purani.
      Hazaaron baar repeat karo. Kuch baar (restarts) chalake best key lo.

>> Chhota example (concept)
   Cipher text mein 'X' sabse zyada aaya -> guess X = E.
   Decrypt: "THE" ki jagah "TNE" aa raha hai -> H aur N ki mapping swap karo
   -> score badh gaya ("THE" bahut common hai) -> swap rakho. Yahi hill climbing hai.

>> Kyun kaam karta hai? (intuition)
   - Substitution letter ka NAAM badalta hai, uski frequency aur pattern nahi.
     "THE" har jagah same 3 cipher letters ban jaata hai.
   - Sahi key ke paas decrypted text sabse zyada English jaisa dikhta hai,
     isliye score function sahi key ki taraf le jaata hai.
   - English reference: Python ke andar built-in modules (os, argparse ...) ki
     documentation English mein likhi hai (module.__doc__) -> wahi reference
     text use kiya, alag se lamba text type nahi karna padta.

>> Kahan use hota hai?
   - Historical ciphers todne mein (Mary Queen of Scots cipher, newspaper cryptograms)
   - Cryptanalysis ka basic lesson: key space bada hona KAAFI nahi hai,
     ciphertext mein pattern leak nahi hone chahiye.
   - Modern ciphers (AES) mein confusion + diffusion isi weakness ko hatate hain.

>> Exam trick (yaad rakhne ke liye)
   "count -> ETAOIN guess -> swap -> score -> keep if better"
   Code mein 4 functions: clean, score, climb, crack.

>> Viva Questions
   Q1. Mono-alphabetic cipher ka key space kitna hai?
       Ans: 26! ≈ 4 x 10^26.
   Q2. Itna bada key space phir bhi weak kyun?
       Ans: Har letter ki mapping fixed hai, toh letter frequency aur patterns
            (TH, THE, ING) ciphertext mein waise hi dikhte hain.
   Q3. Frequency analysis kya hai?
       Ans: Ciphertext ke letters count karke unhe English ke common letters
            (E, T, A, O ...) se match karna.
   Q4. English ke sabse common letters?
       Ans: ETAOIN SHRDLU. E ~12.7%, T ~9.1%, A ~8.2%.
   Q5. Sirf frequency analysis se poora decrypt kyun nahi hota?
       Ans: Chhote text mein frequencies thodi alag hoti hain, aur close
            frequency wale letters (jaise H, R, S) aapas mein mix ho jaate hain.
            Isliye bigram/trigram scoring + hill climbing chahiye.
   Q6. Hill climbing kya hai?
       Ans: Optimization technique - chhota random change (2 letters swap) karo,
            agar result better hai toh rakho. Dheere dheere best key tak pahunchte hain.
   Q7. Restarts kyun?
       Ans: Hill climbing local maximum mein atak sakta hai. Alag random runs
            se sabse best result lete hain.
   Q8. Caesar cipher aur mono-alphabetic mein fark?
       Ans: Caesar = sirf 26 keys (shift), mono-alphabetic = 26! keys (koi bhi shuffle).
   Q9. Rare letters (J, Q, X, Z) galat kyun aa sakte hain?
       Ans: Text mein 0-1 baar aate hain, unke liye statistics kam hain.
   Q10. Is weakness ka fix?
       Ans: Poly-alphabetic cipher (Vigenere, Exp 7) - same letter alag jagah
            alag letter banta hai, frequencies flat ho jaati hain.
"""


# =====================================================================
# PART 1: CODE SAMJHO (Part 2 wala code + har line ka manual)
# =====================================================================
# Neeche bilkul wahi code hai jo PART 2 mein hai, bas har line ke saath
# explanation. (Is program mein input() nahi hai, toh kuch replace nahi kiya.)
print("===== PART 1: Annotated version =====")

# math   -> maths functions. Hum sirf math.log(x) use karte hain = natural log (ln x).
#           math.log(1) = 0, math.log(100) ≈ 4.6. Log isliye ki bahut common n-grams
#           (jaise "THE") score ko poori tarah dominate na karein.
# random -> random.sample(seq, k): seq mein se k ALAG-ALAG random items ki list.
#             random.sample(range(26), 2) -> jaise [3, 17] (do alag positions)
#             random.sample(A, 26)        -> A ke 26 letters shuffle ho ke (random key)
import math, random

# Yeh modules sirf unke __doc__ (documentation string) ke liye import kiye hain.
#   m.__doc__ -> har module ke saath aata hua English paragraph(s). Yahi hamara
#   "English sample" hai jisse seekhte hain ki English mein kaunse letter-pairs common hain.
#   (Exam PC pe internet / extra file nahi hogi, toh Python ke andar se hi English le li.)
# collections -> collections.Counter(iterable): har item kitni baar aaya, gin ke dict deta hai.
#   Counter("HELLO") -> {'L': 2, 'H': 1, 'E': 1, 'O': 1}
#   Special: jo key nahi hai uska value 0 deta hai (KeyError nahi). Counter("AB")["Z"] -> 0
import os, argparse, subprocess, unittest, collections

A = 'ABCDEFGHIJKLMNOPQRSTUVWXYZ'


# Text ko saaf karo: sirf CAPITAL letters aur single spaces bacho.
#   t.upper()          -> sab capital
#   .split()           -> whitespace (space, newline, tab) pe tod ke words ki list
#   ' '.join(words)    -> words ko single space se jodo (extra spaces/newlines gaye)
#   ch in A + ' '      -> sirf letter ya space rakho (comma, full stop, digits hata do)
def clean(t):
    return ''.join(ch for ch in ' '.join(t.upper().split()) if ch in A + ' ')


# REF = bada English text (5 modules ke docs jod ke), clean kiya hua.
REF = clean(' '.join(m.__doc__ for m in [os, argparse, subprocess, unittest, collections]))
# NG = har 1-letter, 2-letter, 3-letter tukde (n-gram) ka count REF mein.
#   REF[i:i + n] -> position i se n characters (slicing). Jaise "THE" -> "T","H","E","TH","HE","THE"
#   range(len(REF) - n + 1) -> har possible starting position
NG = collections.Counter(REF[i:i + n] for n in (1, 2, 3) for i in range(len(REF) - n + 1))


# Score = text kitna "English jaisa" hai. Har n-gram ka log(count + 1) jodo.
#   Common tukde ("TH", "THE", "E ") -> bada count -> bada score.
#   Ajeeb tukde ("QZ", "XKJ") -> NG mein nahi -> Counter 0 deta hai -> log(1) = 0.
#   "+ 1" isliye ki log(0) undefined hai.
def score(t):
    return sum(math.log(NG[t[i:i + n]] + 1) for n in (1, 2, 3) for i in range(len(t) - n + 1))


# Key ke saath decrypt: cipher ka A -> key[0], B -> key[1], ... (key = 26-letter string)
#   str.maketrans(x, y) -> translation table banata hai: x[i] ko y[i] se replace karo
#                          (dono same length ke strings). Return: dict {ord(x[i]): ord(y[i])}
#   c.translate(table)  -> c ke har character pe table lagao. Table mein nahi (jaise space)
#                          toh as-it-is rehta hai.
def decrypt(c, key):
    return c.translate(str.maketrans(A, key))


# HILL CLIMBING: key mein do letters swap karo; agar text zyada English lage toh rakho.
def climb(c, key):
    best = score(decrypt(c, key))            # abhi wali key ka score
    for _ in range(3000):                    # 3000 baar try (`_` = loop variable use nahi)
        i, j = random.sample(range(26), 2)   # do alag random positions
        k = list(key)                        # string immutable hai, isliye list banao
        k[i], k[j] = k[j], k[i]              # swap (Python tuple trick)
        k = ''.join(k)                       # wapas string
        s = score(decrypt(c, k))
        if s >= best:                        # better (ya barabar) -> nayi key accept
            key, best = k, s                 # ">=" se barabar wale bhi accept -> atakta kam hai
    return best, key                         # tuple: (score, key) - max() isi pe compare karega


def crack(c):
    # FREQUENCY ANALYSIS se starting key:
    #   sorted(A, key=c.count, reverse=True) -> letters ko cipher mein unke count ke hisaab
    #   se sort karo, sabse zyada wala pehle. key= ek function leta hai jo har item ka
    #   "sort value" deta hai; c.count('X') = c mein 'X' kitni baar aaya.
    order = sorted(A, key=c.count, reverse=True)
    # 'ETAOIN...' = English letters sabse common se kam common tak.
    #   Cipher ka sabse common letter -> E, doosra -> T, ... (pehla andaaza)
    #   order.index(x) -> cipher letter x frequency ranking mein kaunse number pe hai
    key = ''.join('ETAOINSHRDLCUMWFGYPBVKJXQZ'[order.index(x)] for x in A)
    # 3 baar climb chalao (random hai, kabhi atak jaata hai) aur best result lo.
    #   max() tuples ko pehle element (score) se compare karta hai -> highest score wala.
    #   [1] -> us tuple ka key.
    return max(climb(c, key) for _ in range(3))[1]


TEXT = """Cryptography is the practice of securing communication in the presence of
adversaries. A classical cipher such as the Vigenere cipher uses a repeating keyword
to shift each letter of the message by a different amount. For a long time it was
believed to be unbreakable, but the repetition of the key leaves patterns in the
ciphertext. Once the length of the key is known, the message splits into several
simple shift ciphers, and each of them can be solved by comparing its letter counts
with the normal frequencies of the English language."""

P = clean(TEXT)                                  # plaintext: capitals + spaces
secret = ''.join(random.sample(A, 26))           # random substitution key (26! possible)
C = P.translate(str.maketrans(A, secret))        # ENCRYPT: A -> secret[0], B -> secret[1], ...
print("Ciphertext:", C)

D = decrypt(C, crack(C))                         # sirf ciphertext se key dhoondo, decrypt karo
print("Plaintext :", D)
print("Correct   :", D == P)                     # original se match? (kabhi 1-2 rare letters galat)


# =====================================================================
# PART 2: EXAM VERSION (bina comments - yahi likhna hai / ratna hai)
# =====================================================================
print("\n===== PART 2: Exam version =====")

import math, random
import os, argparse, subprocess, unittest, collections

A = 'ABCDEFGHIJKLMNOPQRSTUVWXYZ'


def clean(t):
    return ''.join(ch for ch in ' '.join(t.upper().split()) if ch in A + ' ')


REF = clean(' '.join(m.__doc__ for m in [os, argparse, subprocess, unittest, collections]))
NG = collections.Counter(REF[i:i + n] for n in (1, 2, 3) for i in range(len(REF) - n + 1))


def score(t):
    return sum(math.log(NG[t[i:i + n]] + 1) for n in (1, 2, 3) for i in range(len(t) - n + 1))


def decrypt(c, key):
    return c.translate(str.maketrans(A, key))


def climb(c, key):
    best = score(decrypt(c, key))
    for _ in range(3000):
        i, j = random.sample(range(26), 2)
        k = list(key)
        k[i], k[j] = k[j], k[i]
        k = ''.join(k)
        s = score(decrypt(c, k))
        if s >= best:
            key, best = k, s
    return best, key


def crack(c):
    order = sorted(A, key=c.count, reverse=True)
    key = ''.join('ETAOINSHRDLCUMWFGYPBVKJXQZ'[order.index(x)] for x in A)
    return max(climb(c, key) for _ in range(3))[1]


TEXT = """Cryptography is the practice of securing communication in the presence of
adversaries. A classical cipher such as the Vigenere cipher uses a repeating keyword
to shift each letter of the message by a different amount. For a long time it was
believed to be unbreakable, but the repetition of the key leaves patterns in the
ciphertext. Once the length of the key is known, the message splits into several
simple shift ciphers, and each of them can be solved by comparing its letter counts
with the normal frequencies of the English language."""

P = clean(TEXT)
secret = ''.join(random.sample(A, 26))
C = P.translate(str.maketrans(A, secret))
print("Ciphertext:", C)

D = decrypt(C, crack(C))
print("Plaintext :", D)
print("Correct   :", D == P)
