// B230038CS - Yash Gupta - Lab 2

/*
 * Prog 5. Write a program for the Rabin-Karp algorithm.
 * Using the written program,
 * find out number of spurious hits
 * does the Rabin-Karp matcher encounter in the text
 * T = 3141592653589793 when looking for the pattern P = 26.
 * Consider working modulo q = 11.
 */

int StringLen(char *str) {
  int i = 0;
  for (; str[i] != '\0'; i++)
    ;
  return i;
}

void RabinKarp(char *txt, char *pat, int d, int q) {
  int n = StringLen(txt);
  int m = StringLen(pat);
}
int main() {
  char *txt = "3141592653589793";
  char *pat = "26";
  int d = 10;
  int q = 11;
  RabinKarp(txt, pat, d, q);
}
