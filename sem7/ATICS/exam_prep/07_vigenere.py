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
    result = ''
    for i in range(len(text)):          # i = position 0, 1, 2, ...
        p = A.index(text[i])            # text ka letter -> number. A.index('K') = 10
        k = A.index(key[i % len(key)])  # key repeat: key "KEY", i = 4 -> 4 % 3 = 1 -> key[1] = 'E'
        # (p + k) % 26 -> wrap around (Z ke baad A). Python mein -3 % 26 = 23, toh decrypt bhi sahi.
        result += A[(p + sign * k) % 26]
    return result


# --- Index of Coincidence (IC) ------------------------------------------
# IC = random 2 letters uthao, dono same hone ki probability
#    = sum f(f-1) / N(N-1)     (f = har letter ka count, N = total letters)
# English text ~ 0.066, random/mixed text ~ 0.038.
# Caesar shift karne se IC nahi badalta (letters bas rename hote hain, counts same).
def ic(s):
    N = len(s)
    total = 0
    for ch in A:
        f = s.count(ch)                 # s.count(ch) -> s mein ch kitni baar. "HELLO".count('L') = 2
        total += f * (f - 1)
    # (N = 0 ya 1 ho toh division by zero - isliye text lamba hona chahiye ~300+ letters)
    return total / (N * (N - 1))


# --- Key length estimation ----------------------------------------------
def key_length(c):
    avg_ics = []                        # avg_ics[0] = m=1 ka IC, avg_ics[1] = m=2 ka IC, ...
    for m in range(1, 13):              # try key length 1 se 12 (13 exclude)
        total = 0
        for i in range(m):
            # c[i::m] -> SLICING [start:stop:step]: index i se shuru, har m-th letter = i-th column.
            #   "ABCDEFG"[1::3] = "BE"  (index 1, 4)
            # Agar m sahi hai, har column ek hi key letter se shift hua -> simple Caesar
            # -> uska IC English jaisa (~0.066).
            total += ic(c[i::m])
        avg_ics.append(total / m)       # saare columns ka average IC
    best = max(avg_ics)                 # max(list) -> sabse bada value
    # Problem: key length 3 ho toh 6, 9, 12 pe bhi columns pure Caesar hote hain
    # (multiples bhi high IC) -> sirf max lena galat ho sakta hai.
    # Rule: SABSE CHHOTA m jiska IC best ke 90% ke upar hai.
    for m in range(1, 13):
        if avg_ics[m - 1] >= 0.9 * best:   # m - 1 kyunki list index 0 se shuru hota hai
            return m


# --- Chi-squared: text kitna English jaisa hai --------------------------
# chi^2 = sum (observed - expected)^2 / expected
# Jitna CHHOTA chi^2, utna English ke kareeb.
def chi_sq(s):
    N = len(s)
    total = 0
    for i in range(26):
        observed = s.count(A[i])            # text mein yeh letter asal mein kitni baar aaya
        expected = N * FREQ[i] / 100        # English hota toh N letters mein kitni baar aata
        total += (observed - expected) ** 2 / expected
    return total


# --- Crack: key length -> har column ka key letter ----------------------
def crack(c):
    m = key_length(c)
    key = ''
    for i in range(m):
        col = c[i::m]                   # i-th column (ek hi key letter se encrypt hua)
        # Is column ko 26 possible shifts (A..Z) se decrypt karke dekho,
        # jis shift ka chi^2 sabse kam -> wahi key letter.
        best_shift = 0
        best_score = chi_sq(vigenere(col, A[0], -1))   # pehle shift 0 ('A') ko best maan lo
        for k in range(1, 26):
            score = chi_sq(vigenere(col, A[k], -1))    # A[k] = key letter (k = 18 -> 'S')
            if score < best_score:                     # isse better (kam) mila? -> update
                best_score = score
                best_shift = k
        key += A[best_shift]
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
P = ''
for ch in TEXT.upper():
    if ch in A:
        P += ch

# raw = input("Enter key (letters, max 12): ").upper()
#   Edge cases: user ne lowercase/space/number daala -> neeche loop sirf A-Z rakhega.
#   Max 12 kyunki key_length() sirf 1..12 check karta hai.
raw = 'SECRET'
key = ''
for ch in raw:
    if ch in A:
        key += ch
if key == '':                           # kuch bhi nahi daala -> default key
    key = 'KEY'

C = vigenere(P, key)                    # encrypt (sign default = 1)
print("Ciphertext:", C)

# crack tuple return karta hai -> do variables mein unpack.
found_key, plain = crack(C)
print("Key length:", len(found_key))
print("Found key:", found_key)
print("Plaintext:", plain)


# =====================================================================
# PART 2: EXAM VERSION (bina comments - yahi likhna hai / ratna hai)
# =====================================================================
print("\n===== PART 2: Exam version =====")

A = 'ABCDEFGHIJKLMNOPQRSTUVWXYZ'
FREQ = [8.2, 1.5, 2.8, 4.3, 12.7, 2.2, 2.0, 6.1, 7.0, 0.2, 0.8, 4.0, 2.4,
        6.7, 7.5, 1.9, 0.1, 6.0, 6.3, 9.1, 2.8, 1.0, 2.4, 0.2, 2.0, 0.1]


def vigenere(text, key, sign=1):
    result = ''
    for i in range(len(text)):
        p = A.index(text[i])
        k = A.index(key[i % len(key)])
        result += A[(p + sign * k) % 26]
    return result


def ic(s):
    N = len(s)
    total = 0
    for ch in A:
        f = s.count(ch)
        total += f * (f - 1)
    return total / (N * (N - 1))


def key_length(c):
    avg_ics = []
    for m in range(1, 13):
        total = 0
        for i in range(m):
            total += ic(c[i::m])
        avg_ics.append(total / m)
    best = max(avg_ics)
    for m in range(1, 13):
        if avg_ics[m - 1] >= 0.9 * best:
            return m


def chi_sq(s):
    N = len(s)
    total = 0
    for i in range(26):
        observed = s.count(A[i])
        expected = N * FREQ[i] / 100
        total += (observed - expected) ** 2 / expected
    return total


def crack(c):
    m = key_length(c)
    key = ''
    for i in range(m):
        col = c[i::m]
        best_shift = 0
        best_score = chi_sq(vigenere(col, A[0], -1))
        for k in range(1, 26):
            score = chi_sq(vigenere(col, A[k], -1))
            if score < best_score:
                best_score = score
                best_shift = k
        key += A[best_shift]
    return key, vigenere(c, key, -1)


TEXT = """Cryptography is the practice of securing communication in the presence of
adversaries. A classical cipher such as the Vigenere cipher uses a repeating keyword
to shift each letter of the message by a different amount. For a long time it was
believed to be unbreakable, but the repetition of the key leaves patterns in the
ciphertext. Once the length of the key is known, the message splits into several
simple shift ciphers, and each of them can be solved by comparing its letter counts
with the normal frequencies of the English language."""

P = ''
for ch in TEXT.upper():
    if ch in A:
        P += ch

raw = input("Enter key (letters, max 12): ").upper()
key = ''
for ch in raw:
    if ch in A:
        key += ch
if key == '':
    key = 'KEY'

C = vigenere(P, key)
print("Ciphertext:", C)

found_key, plain = crack(C)
print("Key length:", len(found_key))
print("Found key:", found_key)
print("Plaintext:", plain)
