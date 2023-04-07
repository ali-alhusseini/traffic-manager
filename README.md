# Traffic Manager

## Overview
Traffic Manager is a C program designed as part of a school project on dealock 
and synchronization concepts in Operating Systems.

## Description
The program implements a junction crossing scenario that has four directions (North, West, South, East)
and buses may come from all directions. The program ensures that there is only one bus crossing the 
junction at a time using semaphores to lock and unlock the junction.

Every bus waits if there is already a bus at the junction from its own 
direction and also gives precedence to the bus coming from its right side.

```
Junction Diagram:

                    North
                    ↓
                   |  .  |
                   |  .  |
                   |  .  |
                   |  .  |
        ⏤⏤⏤⏤⏤⏤   .   ⏤⏤⏤⏤⏤⏤ ←
   West . . . . . . . . . . . . . . .  East
     →  ⏤⏤⏤⏤⏤⏤   .   ⏤⏤⏤⏤⏤⏤
                   |  .  |
                   |  .  | 
                   |  .  |
                   |  .  |
                        ↑
                    South
```

The program is using a matrix of size n * m where n is the number of buses we
read from "sequence.txt" , which can be changed, and m is the number of 
semaphores, which in our case is 4: north, west, south, east. The matrix 
is saved into the file "matrix.txt" which is initally created by manager.c 
and then updated by bus.c by the different bus processes.

Each entery in the matrix [i][j] can have one of three values:
- 0 >> bus hasn't requested or released semaphore.
- 1 >> bus requested semaphore.
- 2 >> bus acquired lock for semaphore.

>The matrix would look like this if initialized using 4 bus processes:

|  Buses | North | West | South | East |
|  ----- | ----- | ---- | ----- | ---- |
| **NB** |   0   |   0  |   0   |   0  |
| **WB** |   0   |   0  |   0   |   0  |
| **SB** |   0   |   0  |   0   |   0  |
| **EB** |   0   |   0  |   0   |   0  |

At every iteration with p probability we check for a deadlock. Deadlock 
detection is implemeneted by checking for 4 pairs of repeating 2 and 1 in 
the matrix.

>A possible deadlock scenario would have a matrix as follows:

|  Buses | North | West | South | East |
|  ----- | ----- | ---- | ----- | ---- |
| **NB** |   2   |   1  |   0   |   0  |
| **WB** |   0   |   2  |   1   |   0  |
| **SB** |   0   |   0  |   2   |   1  |
| **EB** |   1   |   0  |   0   |   2  |


## Running the Program

**Compile:**

Use the C comiler `gcc` to compile the files in the following order:
1. Compile `bus.c` using the `-pthread` flag.

     `gcc -pthread -o bus bus.c`

2. Compile `manager.c`

     `gcc -o manager manager.c`

**Run:**

Run the program from `manager.c`

`./manager [p value 0.2 to 0.7]`

## Contributors
- [Ali Alhusseini](https://github.com/ali-alhusseini)
- [Riley O'Keefe](https://github.com/R0keefe)
