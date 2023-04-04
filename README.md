# Traffic Manager

## Overview
Traffic Manager is a C program designed as part of a school project on dealock 
and synchronization concepts in Operating Systems.

## Description
The program implements a junction crossing scenario that has four directions 
(North, West, South, East) and buses may come from all directions. 
The progrma ensures that there is only on bus crossing the junction at a 
time using semaphores to lock and unlock the junction. 

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

Step 1: 

-create a sequence.txt file outside of the programs which the manager.c program will read in

-read the characters from the sequence.txt into a character array and then extract each character

Step 2:

-create a matrix.txt file within the manager.c program which will have a size of n X m, where n = length of the char array read from sequence.txt and m = the semaphores N,W,S,E

-initialize all the values of the matrix.txt to zero

-matrix.txt will store the resource request and resource allocation of various buses

Step 3:

-take probability read in from command line (between 0.2-0.7) and check this probability against a value r (random number between 0-1)

-if r < p then call a deadlock function

-create a deadlock function that will check if there is deadlock in the sequence of directions given in sequence.txt

-the deadlock function will use depth first search algorithm which will intially search from one node in the graph and then travel through all the nodes in the graph and IF it reaches the back edge of a previously seen node a cycle is declared AKA deadlock

-if deadlock does not occur then the inside a while(1) loop, child processes will be created using fork() and after a child process has been created the child process will be replaced using a execlp("bus", [direction], [bus pid]). 

-the parent will continue replacing the child processes with execlp until all directions in the sequence array have been read 

step 4: Cycle Detection Algorithm uses one dynamic data stucture L, a list of nodes, as well as arcs. to prevent repeated inspections arcs will be marked to indicate they have already been inspected.

REFERENCE: Andrew S. Tanenbaum - Modern Operating Systems - Section 6.4.1 Page 445

        1. for each node N in the graph perform the following five steps with N as the staring node.

        2. Initialize L to the empty list and designate all unmarked outgoing arcs

        3. Add the current node to the end of L and check to see if the node now appears in L two times. if it does, the graph contains a cycle(listed in L) and the algorithm terminates

        4. From the given node see if there are any unmarked outgoing arcs. If so, go to step 5. if not go to step 6.

        5. Pick an unmarked outgoing arc at random and mark it. Then follow it to the new current node and go to step 3.

        6. If this node is the intitial node, the graph does not contain any cycles and the algorithm terminates. Otherwise we have now reached a dead end. Remove it and go back to the previous node, that is the one that was current just before this one, make that one the current node and go to step 3.

QUESTIONS:
-does the matrix file need to be created within the program or can we just create a file and write to it?

-are all 6 of the semaphores used in bus.c only?

-does the creation of the random variable r need to be inside the while(TRUE) loop so the program creates a new random variable and checks it against the probability p each time

-ask if we can use algorithm found online https://www.scaler.com/topics/dfs-program-in-c/?

-what is meant by "with 1-p probability it creates the next bus process" in the project description?

REFERENCES:
https://www.youtube.com/watch?v=Cwa8AQ4rIwg

https://www.scaler.com/topics/dfs-program-in-c/

https://www.geeksforgeeks.org/c-program-to-count-the-number-of-characters-in-a-file/

https://cboard.cprogramming.com/c-programming/150672-read-strings-text-file-into-char-array.html

https://www.programiz.com/c-programming/c-file-input-output

https://blog.udemy.com/fopen-c/

https://dyclassroom.com/c/c-file-handling-read-and-write-integers