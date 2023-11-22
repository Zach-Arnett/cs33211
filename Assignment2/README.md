# Programming Assignment #2
## Banker's Algorithm
An implementation of the Banker's Algorithm using C++ in a Linux environment

## Explaination
banker.cpp reads from banker.txt to obtain the number of processes, number of resources, allocated resources, max resources, and available resources. The program utilizes the banker's algorithm to determine if the system is in a safe state. If so, it prints out the safe sequence.

## Usage
To compile and run, use the following:
```bash
g++ banker.cpp -o banker
./banker
```

## Documentation and Examples
Edit data.txt to change the number of processes, number of resources, allocated resources, max resources, and available resources

the first value is the number of processes
the second value is the number of resources
for example, the following sets 5 processes and 3 resources:
```bash
5 3
```

Next is the matrix for allocated resources. it will have (num of processes)x(num of resources) values. 
This example shows a 5x3 matrix for allocated resources.
```bash
5 3

0 1 0
2 0 0
3 0 2
2 1 1
0 0 2
```

Next is the matrix for max resources. it will have (num of processes)x(num of resources) values. 
This example shows a 5x3 matrix for allocated resources and max resources.
```bash
5 3

0 1 0
2 0 0
3 0 2
2 1 1
0 0 2

7 5 3
3 2 2
9 0 2
2 2 2
4 3 3
```

Lastly is the matrix for available resources. it will have (num of resources) values. 
This example shows a 5x3 matrix for allocated resources and max resources and a 1x3 matrix for available resources.
```bash
5 3

0 1 0
2 0 0
3 0 2
2 1 1
0 0 2

7 5 3
3 2 2
9 0 2
2 2 2
4 3 3

3 3 2
```
