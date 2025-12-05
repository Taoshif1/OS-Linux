#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

int readcount = 0;
int data = 0;

pthread_mutex_t rmutex;
sem_t wmutex;

void* reader(void* arg) {
    int id = (int)(long)arg;

    while (1) {
        pthread_mutex_lock(&rmutex);
        readcount++;
        if (readcount == 1)
            sem_wait(&wmutex);
        pthread_mutex_unlock(&rmutex);

        printf("Reader %d reads data = %d\n", id, data);
        usleep(100000);

        pthread_mutex_lock(&rmutex);
        readcount--;
        if (readcount == 0)
            sem_post(&wmutex);
        pthread_mutex_unlock(&rmutex);

        usleep(200000);
    }
}

void* writer(void* arg) {
    int id = (int)(long)arg;

    while (1) {
        sem_wait(&wmutex);

        data++;
        printf("Writer %d writes data = %d\n", id, data);
        usleep(200000);

        sem_post(&wmutex);

        usleep(300000);
    }
}

int main() {
    pthread_t r1, r2, w1;

    pthread_mutex_init(&rmutex, NULL);
    sem_init(&wmutex, 0, 1);

    pthread_create(&r1, NULL, reader, (void*)1);
    pthread_create(&r2, NULL, reader, (void*)2);
    pthread_create(&w1, NULL, writer, (void*)1);

    pthread_join(r1, NULL);
    pthread_join(r2, NULL);
    pthread_join(w1, NULL);
}
