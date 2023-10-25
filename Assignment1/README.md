# Programming Assignment #1
## Producer-Consumer Problem

An implementation of the Producer-Consumer Problem using C/C++ in a Linux environment


## Compilation
To compile and run, use the following:

```bash
gcc producer.c -pthread -lrt -o producer
gcc consumer.c -pthread -lrt -o consumer
./producer & ./consumer &
```