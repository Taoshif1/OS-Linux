#include <stdio.h>
#include <pthread.h>

#define SIZE 1000
#define THREADS 4

int arr[SIZE];
pthread_mutex_t lock;

void* update_array(void* arg) {
    long id = (long)arg;

    for (int i = 0; i < SIZE; i++) {
        pthread_mutex_lock(&lock);
        arr[i] += id;   // safe update
        pthread_mutex_unlock(&lock);
    }

    return NULL;
}

int main() {
    pthread_t t[THREADS];

    pthread_mutex_init(&lock, NULL);

    for (int i = 0; i < THREADS; i++)
        pthread_create(&t[i], NULL, update_array, (void*)(long)i);

    for (int i = 0; i < THREADS; i++)
        pthread_join(t[i], NULL);

    pthread_mutex_destroy(&lock);

    printf("Array[0] = %d\n", arr[0]);
    printf("Array[999] = %d\n", arr[999]);

    return 0;
}
