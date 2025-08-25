#include <stdio.h>

int strLen(char *pat) {
  int i = 0;
  while (pat[i] != '\0') {
    i++;
  }
  return i;
}

void Naive(char *pat, char *txt) {
  int M = strLen(pat);
  int N = strLen(txt), i, j;
  for (i = 0; i <= N - M; i++) {
    for (j = 0; j < M; j++)
      if (txt[i + j] != pat[j])
        break;
    if (j == M)
      printf("Pattern found at  index %d.\n", i);
  }
}

void Modified_Naive(char *pat, char *txt) {
  int M = strLen(pat);
  int N = strLen(txt), i = 0;
  do {
    int j = 0;
    if (txt[i + j] == pat[j]) {
      for (j = 0; j < M; j++)
        if (txt[i + j] != pat[j])
          break;
      if (j == M)
        printf("Pattern found  at index %d.\n", i);
      i = i + j;
    } else
      i++;
  } while (i <= N);
}

int main() {
  char txt[] = "AABAACAADAABAAABAA";
  char pat[] = "AABA";
  printf("Running Naive String Matcher: \n");
  Naive(pat, txt);
  printf("\nRunning Modified Naive String Matcher: \n");
  Modified_Naive(pat, txt);
  return 0;
}
