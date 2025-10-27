// B230038CS - Yash Gupta - Lab 5

#include <stdio.h>

#define MAXSIZE 100

int Pow(int x, int y) {
  int pow = 1;
  for (int i = 0; i < y; i++) {
    pow *= x;
  }
  return pow;
}

int strLen(char *str) {
  int i = 0;
  while (str[i++] != '\0')
    ;
  return --i;
}

void rabin_karp_matcher(char *T, char *P, int d, int q) {
  int n = strLen(T);
  int m = strLen(P);
  int h = (Pow(d, m - 1)) % q;
  int p = 0, t = 0;
  int spurious_hits = 0;

  for (int i = 0; i < m; i++) {
    p = (d * p + (P[i] - '0')) % q;
    t = (d * t + (T[i] - '0')) % q;
  }

  int found = 0;

  for (int s = 0; s <= n - m; s++) {
    if (p == t) {
      int match = 1;
      for (int i = 0; i < m; i++) {
        if (P[i] != T[s + i]) {
          match = 0;
          break;
        }
      }
      if (match) {
        printf("Pattern found at shift %d\n", s + 1);
        found = 1;
      } else {
        spurious_hits++;
      }
    }

    if (s < n - m) {
      t = (d * (t - (T[s] - '0') * h) + (T[s + m] - '0')) % q;
      if (t < 0)
        t = (t + q) % q;
    }
  }

  if (!found)
    printf("Pattern not found in text\n");

  printf("Number of spurious hits: %d\n", spurious_hits);
}

int main() {
  int d = 10, q = 11;
  printf("Enter d: ");
  scanf("%d", &d);
  printf("Enter q: ");
  scanf("%d", &q);

  char text[MAXSIZE] = "12234321442122342323";
  printf("Enter text: ");
  scanf("%s", text);
  char pat[MAXSIZE] = "2234";
  printf("Enter pattern: ");
  scanf("%s", pat);

  printf("Text: %s\nPattern: %s\n", text, pat);
  printf("Running Rabin-Karp matcher...\n\n");

  rabin_karp_matcher(text, pat, d, q);
  return 0;
}
