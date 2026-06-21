// B230038CS - Yash Gupta - Lab 5

#include <stdio.h>
#include <stdlib.h>

#define MAXSIZE 100

int strLen(char *str) {
  int i = 0;
  while (str[i++] != '\0')
    ;
  return --i;
}

void prefix(char *pattern, int m, int *lps) {
  lps[0] = 0;
  int len = 0;
  int i = 1;

  while (i < m) {
    if (pattern[i] == pattern[len]) {
      len++;
      lps[i] = len;
      i++;
    } else {
      if (len != 0) {
        len = lps[len - 1];
      } else {
        lps[i] = 0;
        i++;
      }
    }
  }
}

void kmp_matcher(char *text, char *pattern) {
  int n = strLen(text);
  int m = strLen(pattern);

  if (m == 0 || m > n) {
    printf("Invalid pattern length\n");
    return;
  }

  int *lps = (int *)malloc(m * sizeof(int));

  prefix(pattern, m, lps);

  printf("Text: %s\n", text);
  printf("Pattern: %s\n", pattern);
  printf("LPS array: ");
  for (int i = 0; i < m; i++) {
    printf("%d ", lps[i]);
  }
  printf("\n\n");

  int i = 0;
  int j = 0;
  int found = 0;

  while (i < n) {
    if (pattern[j] == text[i]) {
      i++;
      j++;
    }

    if (j == m) {
      printf("Pattern found at index %d\n", i - j);
      found = 1;
      j = lps[j - 1];
    } else if (i < n && pattern[j] != text[i]) {
      if (j != 0) {
        j = lps[j - 1];
      } else {
        i++;
      }
    }
  }

  if (!found) {
    printf("Pattern not found in text\n");
  }

  free(lps);
}

int main() {
  char text[MAXSIZE] = "ABABABABAB";
  printf("Enter the text: ");
  scanf("%s", text);
  char pattern[MAXSIZE] = "ABABAB";
  printf("Enter the pattern: ");
  scanf("%s", pattern);
  kmp_matcher(text, pattern);

  return 0;
}
