# Programming Assignment #1
## Producer-Consumer Problem
An implementation of the Producer-Consumer Problem using C/C++ in a Linux environment

## Explaination
The producer generates items onto a table that is a part of shared memory. The consumer will then consume the item. The table can hold up to 2 simultaneous items. When the table is full, the producer will wait. When the table is empty, the consumer will wait. This is performed using semaphores and allows for mutual exclusion.
Both the producer and consumer have a random wait time, meaning that the producer could produce multiple items in a row and the consumer could consume multiple items in a row. This creates a more realistic environment and tests that the producer and consumer can't enter the critical section at the same time.

## Usage
To compile and run, use the following:
```bash
gcc producer.c -pthread -lrt -o producer
gcc consumer.c -pthread -lrt -o consumer
./producer & ./consumer &
```

## Documentation and Examples
These are provided in a the [Documentation File](https://github.com/Zach-Arnett/cs33211/blob/main/Assignment1/DOCUMENTATION.md)
