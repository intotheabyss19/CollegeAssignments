// B230038CS - Yash Gupta - Lab 3

/*
 * Prog 4.
 * (a) Write a program for NAIVE-STRING-MATCHER algorithm
 * (b) Write a program for modified NAIVE-STRING-MATCHER algorithm with O(n)
 * complexity
 */

#include <stdio.h>

#define MAX_STRING_LENGTH 1024

int StringLen(char *pat) {
  int i = 0;
  for (; pat[i] != '\0'; i++)
    ;
  return i;
}

void Naive(char *pat, char *txt) {
  int M = StringLen(pat);
  int N = StringLen(txt), i, j;
  for (i = 0; i <= N - M; i++) {
    for (j = 0; j < M; j++)
      if (txt[i + j] != pat[j])
        break;
    if (j == M)
      printf("Pattern found at %d.\n", i);
  }
}

void Modified_Naive(char *pat, char *txt) {
  int M = StringLen(pat);
  int N = StringLen(txt), i = 0;
  do {
    int j = 0;
    if (txt[i + j] == pat[j]) {
      for (j = 0; j < M; j++)
        if (txt[i + j] != pat[j])
          break;
      if (j == M)
        printf("Pattern found at %d.\n", i);
      i = i + j;
    } else
      i++;
  } while (i <= N);
}

int main() {
  char txt[MAX_STRING_LENGTH];
  char pat[MAX_STRING_LENGTH];
  int i = 0;

  printf("Enter text: ");
  scanf("%s", txt);
  printf("Enter pattern: ");
  scanf("%s", pat);

  printf("Running Naive String Matcher: \n");
  Naive(pat, txt);
  printf("\nRunning Modified Naive String Matcher: \n");
  Modified_Naive(pat, txt);
  return 0;
}
