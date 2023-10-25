// Zach Arnett

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>

#define TABLE_SIZE 2

sem_t *empty;
sem_t *full;
sem_t *mutex;

int *table;

void *producer(void *arg) {
    int item = 1;

    while (1) {
        sem_wait(empty);
        sem_wait(mutex);

        printf("Producing item %d\n", item);
        table[*table] = item;
        *table += 1;
        
        item++;

        sem_post(mutex);
        sem_post(full);

        sleep(1);
    }
}

int main() {
    // Initialize shared memory for table
    int fd = shm_open("/table_memory", O_CREAT | O_RDWR, 0666);
    ftruncate(fd, sizeof(int));
    table = mmap(0, sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);

    // Initialize semaphores
    empty = sem_open("/empty_sem", O_CREAT, 0666, TABLE_SIZE);
    full = sem_open("/full_sem", O_CREAT, 0666, 0);
    mutex = sem_open("/mutex_sem", O_CREAT, 0666, 1);

    pthread_t producer_thread;
    pthread_create(&producer_thread, NULL, producer, NULL);

    pthread_exit(NULL);
}
