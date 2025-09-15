#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int randint(int, int);

int main() {
  srand(time(NULL));
  for ( int i = 0; i < RAND_MAX; i++)
    printf("%d\n", randint(0,6));
  return 0;
}

int randint(int lower, int upper) {
  int n;
  n = lower + (double)((upper - lower) * (double) rand() / (RAND_MAX)) - (RAND_MAX - 1 / (float)RAND_MAX);
  return n;
}
