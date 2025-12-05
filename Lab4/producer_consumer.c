#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

#define BUFFER_SIZE 5

int buffer[BUFFER_SIZE];
int count = 0;

pthread_mutex_t lock;

void* producer(void* arg) {
    for (int i = 0; i < 10; i++) {
        pthread_mutex_lock(&lock);

        if (count < BUFFER_SIZE) {
            buffer[count++] = i;
            printf("Producer produced: %d | Count = %d\n", i, count);
        }

        pthread_mutex_unlock(&lock);
        usleep(100000);
    }
    return NULL;
}

void* consumer(void* arg) {
    for (int i = 0; i < 10; i++) {
        pthread_mutex_lock(&lock);

        if (count > 0) {
            int item = buffer[--count];
            printf("Consumer consumed: %d | Count = %d\n", item, count);
        }

        pthread_mutex_unlock(&lock);
        usleep(150000);
    }
    return NULL;
}

int main() {
    pthread_t p, c;

    pthread_mutex_init(&lock, NULL);

    pthread_create(&p, NULL, producer, NULL);
    pthread_create(&c, NULL, consumer, NULL);

    pthread_join(p, NULL);
    pthread_join(c, NULL);

    pthread_mutex_destroy(&lock);

    return 0;
}
