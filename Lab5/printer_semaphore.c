#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define THREADS 5
#define PRINTERS 3

sem_t printer_sem;

void* print_job(void* arg) {
    int id = (int)(long)arg;

    sem_wait(&printer_sem);
    printf("Thread %d got a printer\n", id);

    sleep(1);  // printing...

    printf("Thread %d released the printer\n", id);
    sem_post(&printer_sem);

    return NULL;
}

int main() {
    pthread_t t[THREADS];

    sem_init(&printer_sem, 0, PRINTERS);

    for (int i = 0; i < THREADS; i++)
        pthread_create(&t[i], NULL, print_job, (void*)(long)i);

    for (int i = 0; i < THREADS; i++)
        pthread_join(t[i], NULL);

    sem_destroy(&printer_sem);
}
