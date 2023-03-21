# Traffic Manager
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

QUESTIONS:
-does the matrix file need to be created within the program or can we just create a file and write to it?

-are all 6 of the semaphores used in bus.c only?

-does the creation of the random variable r need to be inside the while(TRUE) loop so the program creates a new random variable and checks it against the probability p each time

-ask if we can use algorithm found online https://www.scaler.com/topics/dfs-program-in-c/?

-what is meant by "with 1-p probability it creates the next bus process" in the project description?

REFERENCES:
https://www.youtube.com/watch?v=Cwa8AQ4rIwg


