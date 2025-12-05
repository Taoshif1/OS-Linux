#include <stdio.h>
#include <pthread.h>
#include <sys/time.h>

int counter = 0;
pthread_mutex_t lock;

void* safe_increment(void* arg) {
    pthread_mutex_lock(&lock);
    for (int i = 0; i < 500000; i++) counter++;
    pthread_mutex_unlock(&lock);
    return NULL;
}

void* unsafe_increment(void* arg) {
    for (int i = 0; i < 500000; i++) counter++;
    return NULL;
}

long get_time() {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return tv.tv_sec * 1000000 + tv.tv_usec;
}

int main() {
    pthread_t t1, t2;

    // Without mutex
    counter = 0;
    long start = get_time();

    pthread_create(&t1, NULL, unsafe_increment, NULL);
    pthread_create(&t2, NULL, unsafe_increment, NULL);
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    long end = get_time();

    printf("No Mutex Time: %ld microseconds | Counter = %d\n", end - start, counter);

    // With mutex
    pthread_mutex_init(&lock, NULL);
    counter = 0;
    start = get_time();

    pthread_create(&t1, NULL, safe_increment, NULL);
    pthread_create(&t2, NULL, safe_increment, NULL);
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    end = get_time();
    pthread_mutex_destroy(&lock);

    printf("With Mutex Time: %ld microseconds | Counter = %d\n", end - start, counter);

    return 0;
}
