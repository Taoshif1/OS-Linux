#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <sys/time.h>

long get_time() {
    struct timeval t;
    gettimeofday(&t, NULL);
    return t.tv_sec * 1000000 + t.tv_usec;
}

int counter = 0;
pthread_mutex_t m;
sem_t s;

void* mutex_increment(void* arg) {
    pthread_mutex_lock(&m);
    for (int i = 0; i < 500000; i++) counter++;
    pthread_mutex_unlock(&m);
}

void* semaphore_increment(void* arg) {
    sem_wait(&s);
    for (int i = 0; i < 500000; i++) counter++;
    sem_post(&s);
}

int main() {
    pthread_t t1, t2;
    long start, end;

    // Mutex timing
    counter = 0;
    pthread_mutex_init(&m, NULL);
    start = get_time();

    pthread_create(&t1, NULL, mutex_increment, NULL);
    pthread_create(&t2, NULL, mutex_increment, NULL);
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    end = get_time();
    printf("Mutex Time: %ld us\n", end - start);

    // Semaphore timing
    counter = 0;
    sem_init(&s, 0, 1);
    start = get_time();

    pthread_create(&t1, NULL, semaphore_increment, NULL);
    pthread_create(&t2, NULL, semaphore_increment, NULL);
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    end = get_time();
    printf("Semaphore Time: %ld us\n", end - start);
}
