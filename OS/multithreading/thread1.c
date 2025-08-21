#include <stdio.h>
#include <pthread.h>

void* thread(void* i) {
    printf("\tI Exist %d", (int)i);
    printf("\n");
    return NULL;
}

int main() {
    int i = 0;
    pthread_t tid[3];
    while (i < 3) {
        pthread_create(&tid[i], NULL, thread, &i);
        i++;
    }

    pthread_join(tid[0], NULL);
    pthread_join(tid[1], NULL);
    pthread_join(tid[2], NULL);

    return 0;
}
