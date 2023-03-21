#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <semaphore.h>
#include <math.h>
#include <time.h>

int flag = 0;
int matrix[][4] = {0}; //Initialize all values to 0

//change flag to 1 if there's deadlock
int checkDeadlock(); 

int main(int argc, char *argv[])
{
    if (argc == 2)
    {
         double p = atof(argv[1]);
         if (p >= 0 && p <= 1)
         {
            printf("%.2f\n", p);
         }
         else
         {
            printf("Value of p has to be between 0 and 1");
            printf("Press enter to continue...");
            getchar();
         }
    }
    else
    {
        printf("Missing command line argument.\n");
        printf("Program now terminating.");
        printf("Press enter to continue...");
        getchar();
    }


    // Open sequence.txt file and read in sequence directions
    FILE* filePointer;
    char ch;

    filePointer = fopen("sequence.txt", "r");

    if (filePointer == NULL)
    {
        printf("sequence.txt cannot be opened.\n");
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
     * m(columns) number of synchronizing semaphores N, W, S, E
     * initialize matrix.txt values to zero
    */
    FILE* fptr;
    fptr = fopen("matrix.txt", "w");

    if(fptr == NULL){
        printf("Error!");
        exit(1);
    }
    for(int i = 0; i < len; i++){
        for(int j = 0; j < 4; j++){
            fprintf(fptr, "%d", matrix[i][j]);
        }
    }
    fclose(fptr);
    /**
     * CREATE A RANDOM VALUE BETWEEN 0 and 1
    */
    //create a random variable r
    srand(time(NULL));
    float r;
    double p;
    r = (float) rand() / RAND_MAX;
 
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
