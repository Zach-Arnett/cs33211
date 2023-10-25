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

void *consumer_thread(void *arg) {
    while (1) {
        sem_wait(full);
        sem_wait(mutex);

        // Consume item from table
        int item = shared_data->items[shared_data->out];
        printf("Consumed item %d\n", item);
        shared_data->out = (shared_data->out + 1) % BUFFER_SIZE;

        sem_post(mutex);
        sem_post(empty);

        sleep(rand() % 4); // Random Wait Time
    }

    return NULL;
}

int main() {
    // Create and initialize semaphores
    empty = sem_open("/empty_sem", O_CREAT, 0666, BUFFER_SIZE);
    full = sem_open("/full_sem", O_CREAT, 0666, 0);
    mutex = sem_open("/mutex_sem", O_CREAT, 0666, 1);

    // Create shared memory segment
    shm_fd = shm_open("/shared_mem", O_RDWR, 0666);
    shared_data = (SharedData *)mmap(NULL, sizeof(SharedData), PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);

    pthread_t consumer_tid;

    // Create consumer thread
    pthread_create(&consumer_tid, NULL, consumer_thread, NULL);

    // Wait for threads to finish (you may need to handle this differently depending on your application)
    pthread_join(consumer_tid, NULL);

    return 0;
}
