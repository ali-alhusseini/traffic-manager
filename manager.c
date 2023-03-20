#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <semaphore.h>
#include <math.h>
#include <time.h>

//Global variables
int flag = 0;

//Function prototypes
int checkDeadlock(); //change flag to 1 if there's deadlock



int main(int argc, char *argv[])
{
    /**
     * READ IN SEQUENCE.TXT FILE
    */
    // Open sequence.txt file and read in sequence directions
    FILE* filePointer;
    char ch;

    filePointer = fopen("sequence.txt", "r");

    if (filePointer == NULL)
    {
        printf("%s does not exist.\n", "sequence.txt");
    }
    //Determine how many characters are in file
    fseek(filePointer, 0, SEEK_END);
    //Determine length of file
    int len = ftell(filePointer);
    //Move back to beginning of file
    fseek(filePointer, 0, SEEK_SET);
    //Allocate memory for directions use len + 1 to iclude null terminating character
    char *directions = malloc(sizeof(char) * (len + 1));
    int i = 0;

    while((ch = fgetc(filePointer)) != EOF){
        directions[i] = ch;
        i++;
    }
    //Terminate string
    directions[i] = '\0';
    

    if(!fclose(fp)){
        printf("\n%s: closed.\n", "sequence.txt");
    }

    /**
     * TO DO -> CREATE OR WRITE TO A matrix.txt FILE 
     * contains matrix
     * n(rows) = length of char
     * initialize matrix.txt values to zero
    */
    /**
     * CREATE A RANDOM VALUE BETWEEN 0 and 1
    */
    //create a random variable r
    srand(time(NULL));
    float r;
    double p;
    r = (float) rand() / RAND_MAX;

    /**
     * READ IN PROBABILITY P FROM COMMAND LINE
    */
    // Check for command line input
    if (argc == 2)
    {
         p = argv[1];
    }
    else {
        printf("Wrong number of command line arguments.\n");
    }
    /**
     * USE OF WHILE LOOP TO CHECK FOR DEADLOCK/CREATE CHILD PROCESSES
    */
    //while loop to check for deadlock
    while(1){
        if(r < p){
            checkDeadlock();
        }
        if(checkDeadlock() == 0){
            //if 0 then no deadlock is present
            //create child processes
        }
    }
}
