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
int* table;

// Consumer function
void* consumer(void* arg) {

    while (1) {
        sem_wait(full);  // Wait for a filled slot
        sem_wait(mutex); // Enter critical section

        // Consume item from the table
        int item = table[0];
        printf("Consumed item: %d\n", item);

        sem_post(mutex); // Exit critical section
        sem_post(empty); // Signal that a slot is empty

        sleep(2);
    }

    return NULL;
}

int main() {
    // Open existing semaphores
    empty = sem_open("/empty", O_CREAT, 0644, TABLE_SIZE);
    full = sem_open("/full", O_CREAT, 0644, 0);
    mutex = sem_open("/mutex", O_CREAT, 0644, 1);

    // Open existing shared memory for the table
    int shm_fd = shm_open("/table", O_RDWR, 0644);
    table = (int*) mmap(NULL, sizeof(int) * TABLE_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);


    pthread_t consumer_thread;

    pthread_create(&consumer_thread, NULL, consumer, NULL);

    pthread_join(consumer_thread, NULL);  // Wait for consumer thread to finish


    return 0;
}
