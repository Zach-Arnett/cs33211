// Zach Arnett

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
#include <fcntl.h>
#include <sys/mman.h>

#define BUFFER_SIZE 2

// Define shared memory structure
typedef struct {
    int items[BUFFER_SIZE];
    int in;
    int out;
} SharedData;

// Define semaphores
sem_t *empty, *full, *mutex;

int shm_fd;
SharedData *shared_data;

void *producer_thread(void *arg) {
    int item = 1;

    while (1) {
        sem_wait(empty);
        sem_wait(mutex);

        // Produce item and put on table
        shared_data->items[shared_data->in] = item;
        printf("Produced item %d\n", item);
        item++;
        shared_data->in = (shared_data->in + 1) % BUFFER_SIZE;

        sem_post(mutex);
        sem_post(full);

        sleep(rand() % 3); // Random Wait Time
    }

    return NULL;
}

int main() {
    // Clean up
    sem_unlink("/empty_sem");
    sem_unlink("/full_sem");
    sem_unlink("/mutex_sem");
    shm_unlink("/shared_mem");

    // Create and initialize semaphores
    empty = sem_open("/empty_sem", O_CREAT, 0666, BUFFER_SIZE);
    full = sem_open("/full_sem", O_CREAT, 0666, 0);
    mutex = sem_open("/mutex_sem", O_CREAT, 0666, 1);

    // Create shared memory segment
    shm_fd = shm_open("/shared_mem", O_CREAT | O_RDWR, 0666);
    ftruncate(shm_fd, sizeof(SharedData));
    shared_data = (SharedData *)mmap(NULL, sizeof(SharedData), PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);

    pthread_t producer_tid;

    // Create producer thread
    pthread_create(&producer_tid, NULL, producer_thread, NULL);

    // Wait for threads to finish (you may need to handle this differently depending on your application)
    pthread_join(producer_tid, NULL);

    // Clean up
    sem_unlink("/empty_sem");
    sem_unlink("/full_sem");
    sem_unlink("/mutex_sem");
    shm_unlink("/shared_mem");

    return 0;
}
