// Zach Arnett

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>

sem_t *empty;
sem_t *full;
sem_t *mutex;

int *table;

void consume(int item) {
    // Consume item
    printf("Consuming item %d\n", item);
    sleep(2);
}

void *consumer(void *arg) {
    int item;

    while (1) {
        sem_wait(full);
        sem_wait(mutex);

        item = table[*table - 1];
        *table -= 1;

        sem_post(mutex);
        sem_post(empty);

        consume(item);
    }
}

int main() {
    // Initialize shared memory for table
    int fd = shm_open("/table_memory", O_RDWR, 0666);
    table = mmap(0, sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);

    // Initialize semaphores
    empty = sem_open("/empty_sem", O_RDWR);
    full = sem_open("/full_sem", O_RDWR);
    mutex = sem_open("/mutex_sem", O_RDWR);

    pthread_t consumer_thread;
    pthread_create(&consumer_thread, NULL, consumer, NULL);

    pthread_exit(NULL);
}
