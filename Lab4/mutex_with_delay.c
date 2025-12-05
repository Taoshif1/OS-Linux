#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

int counter = 0;
pthread_mutex_t lock;

void* increment_with_delay(void* arg) {
    for (int i = 0; i < 10000; i++) {
        pthread_mutex_lock(&lock);
        usleep(1);  // small delay to show performance drop
        counter++;
        pthread_mutex_unlock(&lock);
    }
    return NULL;
}

int main() {
    pthread_t t1, t2;

    pthread_mutex_init(&lock, NULL);
    counter = 0;

    pthread_create(&t1, NULL, increment_with_delay, NULL);
    pthread_create(&t2, NULL, increment_with_delay, NULL);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    pthread_mutex_destroy(&lock);

    printf("Final Counter (With Delay) = %d\n", counter);

    return 0;
}
