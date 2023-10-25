## Documentation
To use the program the producer and consumer must be compiled as such:
```bash
gcc producer.c -pthread -lrt -o producer
gcc consumer.c -pthread -lrt -o consumer
```
The programs can then be run:
```bash
./producer & ./consumer &
```

The producer will automatically produce incrementing integers and store up to 2 at a time.
The consumer will automatically consume the integers, unless there are none to be consumed.

Through the use of mutual exclusion utilizing semaphores, the producer and consumer will never simultaneously update the table. This ensures that the threads do not interfere with eachother in the critical section.

## Examples
An example of the output when run:

```
Produced item 1
Consumed item 1
Produced item 2
Consumed item 2
Produced item 3
Consumed item 3
Produced item 4
Consumed item 4
Produced item 5
Consumed item 5
Produced item 6
Consumed item 6
Produced item 7
Consumed item 7
Produced item 8
Consumed item 8
Produced item 9
Produced item 10
Consumed item 9
Produced item 11
Consumed item 10
Produced item 12
Consumed item 11
Produced item 13
Consumed item 12
Produced item 14
Consumed item 13
Produced item 15
Consumed item 14
Produced item 16
Consumed item 15
Consumed item 16
Produced item 17
Consumed item 17
Produced item 18
Consumed item 18
Produced item 19
Consumed item 19
Produced item 20
Consumed item 20
```

Due to the random wait times of the producer and consumer, the producer produces item 9 and item 10 before the consumer can consume item 9. However, since the table becomes full, the producer must wait until an item is consumed to produce another item.