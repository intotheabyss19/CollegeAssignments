"""
=====================================================================
 7. Breaking the Vigenere (Poly-alphabetic) Cipher
    using Frequency Analysis and Key-Length Estimation
=====================================================================

>> Vigenere cipher kya hai? (Purpose)
   - POLY-alphabetic cipher: ek keyword (jaise "KEY") baar baar repeat hota hai,
     aur har letter apne key letter jitna shift hota hai.
         Plain : A T T A C K A T D A W N
         Key   : K E Y K E Y K E Y K E Y
         Cipher: K X R K G I K X B K A L
     Formula:  C_i = (P_i + K_(i mod m)) mod 26,   m = key length
               P_i = (C_i - K_(i mod m)) mod 26
   - Same letter (T) alag jagah alag cipher letter ban jaata hai (X, R) ->
     simple frequency analysis (Exp 6) seedha kaam nahi karta.
     Isliye ise kabhi "le chiffre indechiffrable" (unbreakable) kehte the.
   - Is experiment ka kaam: key pata NAHI -> pehle key length nikalo,
     phir key, phir plaintext.

>> Main idea: Vigenere = m alag Caesar ciphers
   Key length m pata ho toh text ko m COLUMNS mein baanto:
     column 0 = letters 0, m, 2m, ...   (sab key[0] se shift hue)
     column 1 = letters 1, m+1, ...     (sab key[1] se shift hue)
   Har column ek simple Caesar cipher hai -> frequency se tod sakte hain.

>> Algorithm
   STEP 1: KEY LENGTH (Index of Coincidence - IC)
     IC = "random 2 letters uthao, dono same hon - uski probability"
        IC = sum f(f-1) / N(N-1)      (f = har letter ki count, N = total)
     English text (ya Caesar-shifted English) -> IC ≈ 0.066
     Random/mixed text                       -> IC ≈ 0.038
     Har m = 1..12 ke liye columns banao, average IC nikalo.
     Sahi m pe har column Caesar hai -> IC ≈ 0.066. Galat m pe ≈ 0.04.
     Dhyan: 2m, 3m bhi high aate hain (unke columns bhi pure Caesar hain),
     isliye "best ka 90% se upar wala SABSE CHHOTA m" lete hain.

   STEP 2: HAR COLUMN KA SHIFT (Chi-squared test)
     Column ko 26 possible shifts se ulta shift karo.
     Har result ke liye chi-squared:  X^2 = sum (observed - expected)^2 / expected
       observed = letter ki count, expected = N * English frequency
     Jo shift sabse KAM X^2 de (English ke sabse close) -> wahi key letter.

   STEP 3: key se poora text decrypt karo.

>> Chhota example (concept)
   Key = "KEY" (m = 3). m = 3 pe teeno columns Caesar hain -> avg IC ≈ 0.07.
   m = 2 pe columns mixed hain -> IC ≈ 0.045. Toh m = 3.
   Column 0 ko 'K' (10) se ulta shift karne pe English jaisa -> key[0] = K.

>> Kyun kaam karta hai? (intuition)
   Key repeat hoti hai -> har m-th letter SAME shift. Repetition hi weakness hai.
   Agar key utni hi lambi ho jitna message aur random ho (One-Time Pad)
   -> yeh attack kaam nahi karega.

>> Kahan use hota hai?
   - Historical: 16th century se WW1 tak use hua. Babbage aur Kasiski ne toda.
   - Lesson: repeating key = pattern = breakable. Isliye modern stream ciphers
     mein keystream kabhi repeat nahi hona chahiye.

>> Exam trick (yaad rakhne ke liye)
   "IC se length, chi-square se letter"
   Columns ka Python trick: c[i::m]  -> i se shuru, har m-th letter.

>> Viva Questions
   Q1. Mono-alphabetic aur poly-alphabetic mein fark?
       Ans: Mono mein ek letter hamesha ek hi letter banta hai. Poly mein
            position ke hisaab se alag letter (multiple alphabets).
   Q2. Vigenere ka formula?
       Ans: C_i = (P_i + K_(i mod m)) mod 26, decrypt mein minus.
   Q3. Index of Coincidence kya hai?
       Ans: Do random letters same hone ki probability. English ~0.066, random ~0.038.
   Q4. Key length nikalne ke 2 methods?
       Ans: (1) Kasiski examination - repeated trigrams ke beech ki distances ka GCD.
            (2) Friedman test / Index of Coincidence (yahan yahi use kiya).
   Q5. Kasiski vs IC?
       Ans: Kasiski repeated sequences dhoondhta hai (lambe text mein achha,
            manual). IC statistical hai, code mein aasaan aur reliable.
   Q6. Key length ke multiples (2m, 3m) bhi high IC kyun dete hain?
       Ans: 2m pe har column mein bhi sirf ek hi key letter ka shift hota hai,
            toh woh bhi pure Caesar hai. Isliye sabse chhota sahi m lete hain.
   Q7. Chi-squared test kya karta hai?
       Ans: Observed letter counts aur English expected counts ka fark napta hai.
            Kam value = English ke zyada close.
   Q8. Har column ka shift brute force kyun ho sakta hai?
       Ans: Sirf 26 shifts hain per column.
   Q9. Kab yeh attack fail hoga?
       Ans: Text bahut chhota ho (columns mein letters kam), ya key
            message jitni lambi aur random ho (One-Time Pad).
   Q10. Vigenere ke repeat key ka modern lesson?
       Ans: Keystream/nonce kabhi reuse nahi karna chahiye.
"""


# =====================================================================
# PART 1: CODE SAMJHO (Part 2 wala code + har line ka manual)
# =====================================================================
# Neeche bilkul wahi code hai jo PART 2 mein hai, bas har line ke saath
# explanation. Sirf ek farak: input() ki jagah fixed value di hai (taaki
# file chalane pe do baar input na maange). Asli input() line comment mein hai.
print("===== PART 1: Annotated version =====")

# Koi import nahi - sab kuch built-in Python se ho jaata hai.

# A = alphabet string. A.index('C') = 2 se letter -> number, A[2] = 'C' se number -> letter.
A = 'ABCDEFGHIJKLMNOPQRSTUVWXYZ'

# Normal English text mein har letter kitne % aata hai (A..Z order mein).
# E sabse zyada (12.7%), phir T (9.1%), A (8.2%)... Z/Q sabse kam (0.1%).
# Chi-squared test isi table se compare karega "yeh text English jaisa hai ya nahi".
FREQ = [8.2, 1.5, 2.8, 4.3, 12.7, 2.2, 2.0, 6.1, 7.0, 0.2, 0.8, 4.0, 2.4,
        6.7, 7.5, 1.9, 0.1, 6.0, 6.3, 9.1, 2.8, 1.0, 2.4, 0.2, 2.0, 0.1]


# --- Vigenere encrypt / decrypt (ek hi function) -----------------------
# Formula: C_i = (P_i + K_(i mod m)) mod 26   |  decrypt: P_i = (C_i - K_(i mod m)) mod 26
# sign = 1 -> encrypt (key add karo), sign = -1 -> decrypt (key subtract karo).
# sign=1 "default argument" hai: vigenere(t, k) likho toh encrypt, vigenere(t, k, -1) toh decrypt.
def vigenere(text, key, sign=1):
    # enumerate(text) -> har letter ke saath uska index deta hai: (0,'C'), (1,'R'), ...
    #   i = position, c = letter.
    # key[i % len(key)] -> key ko repeat karta hai: key "KEY", i = 4 -> key[1] = 'E'
    # A.index(x) -> string mein x ki position (0-25). A.index('K') = 10
    # % 26 -> wrap around (Z ke baad A). Python mein -3 % 26 = 23, toh negative bhi sahi.
    # ''.join(...) -> saare letters ko ek string mein jod deta hai ('' = beech mein kuch nahi).
    return ''.join(A[(A.index(c) + sign * A.index(key[i % len(key)])) % 26] for i, c in enumerate(text))


# --- Index of Coincidence (IC) ------------------------------------------
# IC = random 2 letters uthao, dono same hone ki probability
#    = sum f(f-1) / N(N-1)     (f = har letter ka count, N = total letters)
# English text ~ 0.066, random/mixed text ~ 0.038.
# Caesar shift karne se IC nahi badalta (letters bas rename hote hain, counts same).
def ic(s):
    N = len(s)
    # s.count(c) -> string s mein letter c kitni baar aaya. "HELLO".count('L') = 2
    # (Note: N = 0 ya 1 ho toh division by zero - isliye text lamba hona chahiye ~300+ letters)
    return sum(s.count(c) * (s.count(c) - 1) for c in A) / (N * (N - 1))


# --- Key length estimation ----------------------------------------------
def key_length(c):
    # Har possible key length m = 1..12 try karo (range(1, 13) -> 1 se 12, 13 exclude).
    # c[i::m] -> SLICING [start:stop:step] -> index i se shuru, har m-th letter.
    #   "ABCDEFG"[1::3] = "BE"  (index 1, 4 - step 3)
    #   Agar m sahi key length hai, toh har column ek hi key letter se shift hua ->
    #   har column simple Caesar cipher -> uska IC English jaisa (~0.066).
    # Har m ke liye saare columns ka average IC -> ics list (12 values).
    ics = [sum(ic(c[i::m]) for i in range(m)) / m for m in range(1, 13)]
    # Problem: agar key length 3 hai toh 6, 9, 12 pe bhi columns pure hote hain
    # (multiples bhi high IC) -> sirf max() lena galat answer de sakta hai.
    # Rule: SABSE CHHOTA m jiska IC best ke 90% ke upar hai.
    # enumerate(ics, 1) -> counting 1 se shuru (default 0 hota hai): (1, ic1), (2, ic2) ...
    # next(generator) -> generator ka PEHLA value deta hai (matlab pehla m jo condition pass kare).
    return next(m for m, v in enumerate(ics, 1) if v >= 0.9 * max(ics))


# --- Chi-squared: text kitna English jaisa hai --------------------------
# chi^2 = sum (observed - expected)^2 / expected
#   observed = text mein letter ka count, expected = N * FREQ% / 100
# Jitna CHHOTA chi^2, utna English ke kareeb.
def chi_sq(s):
    N = len(s)
    return sum((s.count(A[i]) - N * FREQ[i] / 100) ** 2 / (N * FREQ[i] / 100) for i in range(26))


# --- Crack: key length -> har column ka key letter ----------------------
def crack(c):
    m = key_length(c)
    key = ''
    for i in range(m):
        col = c[i::m]                  # i-th column (ek hi key letter se encrypt hua)
        # Is column ko 26 possible shifts (A..Z) se decrypt karke dekho.
        # min(iterable, key=function) -> woh element return karta hai jiske liye
        #   function ka value sabse chhota ho. Yahan: woh shift k jiska chi^2 minimum.
        # lambda k: ... -> chhota naam-less function (input k, output chi^2).
        # A[k] = woh key letter (k = 0 -> 'A', k = 18 -> 'S').
        key += A[min(range(26), key=lambda k: chi_sq(vigenere(col, A[k], -1)))]
    # Poori key mil gayi -> poora ciphertext decrypt karo. Return tuple (key, plaintext).
    return key, vigenere(c, key, -1)


# Sample English text (~440 letters). Frequency analysis ko lamba text chahiye,
# chhote text pe counts reliable nahi hote.
TEXT = """Cryptography is the practice of securing communication in the presence of
adversaries. A classical cipher such as the Vigenere cipher uses a repeating keyword
to shift each letter of the message by a different amount. For a long time it was
believed to be unbreakable, but the repetition of the key leaves patterns in the
ciphertext. Once the length of the key is known, the message splits into several
simple shift ciphers, and each of them can be solved by comparing its letter counts
with the normal frequencies of the English language."""

# .upper() -> sab capital. "if ch in A" -> spaces, comma, newline sab hata do (sirf A-Z rakho).
P = ''.join(ch for ch in TEXT.upper() if ch in A)

# key = ''.join(ch for ch in input("Enter key (letters, max 12): ").upper() if ch in A) or 'KEY'
#   Edge cases: user ne lowercase/space/number daala -> sirf A-Z bachenge.
#   Kuch bhi nahi daala ('' empty string falsy hai) -> "or 'KEY'" default key le leta hai.
#   Max 12 kyunki key_length() sirf 1..12 check karta hai.
key = 'SECRET'
C = vigenere(P, key)                   # encrypt (sign default = 1)
print("Ciphertext:", C)

# crack tuple return karta hai -> do variables mein unpack.
found_key, plain = crack(C)
print("Key length:", len(found_key))
print("Found key :", found_key)
print("Plaintext :", plain)


# =====================================================================
# PART 2: EXAM VERSION (bina comments - yahi likhna hai / ratna hai)
# =====================================================================
print("\n===== PART 2: Exam version =====")

A = 'ABCDEFGHIJKLMNOPQRSTUVWXYZ'
FREQ = [8.2, 1.5, 2.8, 4.3, 12.7, 2.2, 2.0, 6.1, 7.0, 0.2, 0.8, 4.0, 2.4,
        6.7, 7.5, 1.9, 0.1, 6.0, 6.3, 9.1, 2.8, 1.0, 2.4, 0.2, 2.0, 0.1]


def vigenere(text, key, sign=1):
    return ''.join(A[(A.index(c) + sign * A.index(key[i % len(key)])) % 26] for i, c in enumerate(text))


def ic(s):
    N = len(s)
    return sum(s.count(c) * (s.count(c) - 1) for c in A) / (N * (N - 1))


def key_length(c):
    ics = [sum(ic(c[i::m]) for i in range(m)) / m for m in range(1, 13)]
    return next(m for m, v in enumerate(ics, 1) if v >= 0.9 * max(ics))


def chi_sq(s):
    N = len(s)
    return sum((s.count(A[i]) - N * FREQ[i] / 100) ** 2 / (N * FREQ[i] / 100) for i in range(26))


def crack(c):
    m = key_length(c)
    key = ''
    for i in range(m):
        col = c[i::m]
        key += A[min(range(26), key=lambda k: chi_sq(vigenere(col, A[k], -1)))]
    return key, vigenere(c, key, -1)


TEXT = """Cryptography is the practice of securing communication in the presence of
adversaries. A classical cipher such as the Vigenere cipher uses a repeating keyword
to shift each letter of the message by a different amount. For a long time it was
believed to be unbreakable, but the repetition of the key leaves patterns in the
ciphertext. Once the length of the key is known, the message splits into several
simple shift ciphers, and each of them can be solved by comparing its letter counts
with the normal frequencies of the English language."""

P = ''.join(ch for ch in TEXT.upper() if ch in A)
key = ''.join(ch for ch in input("Enter key (letters, max 12): ").upper() if ch in A) or 'KEY'
C = vigenere(P, key)
print("Ciphertext:", C)

found_key, plain = crack(C)
print("Key length:", len(found_key))
print("Found key :", found_key)
print("Plaintext :", plain)
