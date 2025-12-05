#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

#define THREADS 5

pthread_mutex_t mutex;
sem_t barrier_sem;
int count = 0;

void* worker(void* arg) {
    int id = (int)(long)arg;

    printf("Thread %d reached barrier\n", id);

    pthread_mutex_lock(&mutex);
    count++;
    if (count == THREADS) {
        for (int i = 0; i < THREADS; i++)
            sem_post(&barrier_sem);
    }
    pthread_mutex_unlock(&mutex);

    sem_wait(&barrier_sem);

    printf("Thread %d passed barrier\n", id);
    return NULL;
}

int main() {
    pthread_t t[THREADS];

    pthread_mutex_init(&mutex, NULL);
    sem_init(&barrier_sem, 0, 0);

    for (int i = 0; i < THREADS; i++)
        pthread_create(&t[i], NULL, worker, (void*)(long)i);

    for (int i = 0; i < THREADS; i++)
        pthread_join(t[i], NULL);

    pthread_mutex_destroy(&mutex);
    sem_destroy(&barrier_sem);
}
