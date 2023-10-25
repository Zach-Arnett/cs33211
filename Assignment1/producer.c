//Zach Arnett

#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>

#define TABLE_SIZE 2

sem_t *empty;
sem_t *full;
sem_t *mutex;

// Producer thread function
void* producer(void* arg) {
    int* table = (int*) arg;  // Cast the argument to a pointer to int (shared memory table)
    int item = 1;

    while (1) {
        sem_wait(empty);  // Wait if there's no space on the table
        sem_wait(mutex);  // Gain exclusive access to the table

        // Produce an item and place it on the table
        table[0] = item;
        printf("Produced item: %d\n", item);

        sem_post(mutex);  // Release access to the table
        sem_post(full);   // Notify that there's an item on the table

        item++;
        sleep(1);
    }

    return NULL;
}

int main() {
    int* table;  // Pointer to shared memory for the table

    // Create and initialize semaphores
    empty = sem_open("/empty", O_CREAT, 0644, TABLE_SIZE);
    full = sem_open("/full", O_CREAT, 0644, 0);
    mutex = sem_open("/mutex", O_CREAT, 0644, 1);

    // Create shared memory for the table
    int shm_fd = shm_open("/table", O_CREAT | O_RDWR, 0644);
    ftruncate(shm_fd, sizeof(int) * TABLE_SIZE);
    table = (int*) mmap(NULL, sizeof(int) * TABLE_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);


    pthread_t producer_thread;

    pthread_create(&producer_thread, NULL, producer, (void*) table);  // Create producer thread

    pthread_join(producer_thread, NULL);  // Wait for the producer thread to finish


    // Close and unlink semaphores
    sem_close(empty);
    sem_close(full);
    sem_close(mutex);
    sem_unlink("/empty");
    sem_unlink("/full");
    sem_unlink("/mutex");

    // Close and unlink shared memory
    close(shm_fd);
    shm_unlink("/table");

    return 0;
}

