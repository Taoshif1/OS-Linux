#include <stdio.h>
#include <pthread.h>

int counter = 0;

void* unsafe_increment(void* arg) {
    for (int i = 0; i < 1000000; i++) {
        counter++;   // no mutex → race condition
    }
    return NULL;
}

int main() {
    pthread_t t[4];

    counter = 0;
    printf("Without Mutex (4 threads):\n");

    for (int i = 0; i < 4; i++)
        pthread_create(&t[i], NULL, unsafe_increment, NULL);

    for (int i = 0; i < 4; i++)
        pthread_join(t[i], NULL);

    printf("Final Counter (No Mutex) = %d\n", counter);

    return 0;
}
