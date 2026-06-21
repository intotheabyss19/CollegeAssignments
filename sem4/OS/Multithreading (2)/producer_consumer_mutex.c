#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define MAX_ITEMS 5
#define BUFFER_SIZE 5

int buffer[BUFFER_SIZE];
int in = 0;
int out = 0;
int produced_count = 0;
int consumed_count = 0;

pthread_mutex_t mutex;
pthread_cond_t empty;

void* producer(void *arg) {
  int item = 1;

  while (produced_count < MAX_ITEMS) {
    pthread_mutex_lock(&mutex);

    while (((in + 1) % BUFFER_SIZE) == out) {
      pthread_cond_wait(&empty, &mutex);
    }

    in = (in + 1) % BUFFER_SIZE;
    buffer[produced_count] = in;
    printf("Produced %d\n", in);

    produced_count++;
  }
  return buffer;
}

void* consumer(void *arg) {
  while (consumed_count > 0) {
    while (((in + 1) % BUFFER_SIZE) == out + 1) {

    }
  }
}

int main() {
    printf("Multithreading getting executed\n");
    
}
