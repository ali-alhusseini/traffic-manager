#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <semaphore.h>
#include <stdarg.h>
#include <math.h>
#include <time.h>

int flag = 0;
int matrix[][4] = {0}; //Initialize all values to 0

//change flag to 1 if there's deadlock
int checkDeadlock(); 

int main(int argc, char *argv[])
{
    double p = 0.0;
    if (argc == 2)
    {
         p = atof(argv[1]);
         if (p >= 0 && p <= 1)
         {
            printf("%.2f\n", p);

            // CODE GOES HERE...
            FILE* filePointer = fopen("sequence.txt", "r");
            if (filePointer == NULL)
            {
                printf("Couldn't open file sequence.txt\n");
            }
            else
            {
                printf("file sequence.txt read successfuly.\n");
            }
         }
         else
         {
            printf("Value of p has to be between 0 and 1\n");
            printf("Program now terminating.\n");
            printf("Press enter to continue...");
            getchar();
         }
    }
    else
    {
        printf("Missing command line argument.\n");
        printf("Program now terminating.\n");
        printf("Press enter to continue...");
        getchar();
    }


     // Open sequence.txt file and read in sequence directions
     char ch;
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

    // /**
    //  * TO DO -> CREATE OR WRITE TO A matrix.txt FILE 
    //  * contains matrix
    //  * n(rows) = length of char
    //  * m(columns) number of synchronizing semaphores N, W, S, E
    //  * initialize matrix.txt values to zero
    // */
     FILE* fptr;
     fptr = fopen("matrix.txt", "w");

     if(fptr == NULL){
         printf("Error!");
         exit(1);
     }
     for(int i = 0; i < len; i++){
         for(int j = 0; j < 4; j++){
             fprintf(fptr, "%d ", matrix[i][j]);
         }
         fprintf(fptr, "\n");
     }
     fclose(fptr);
     /**
      * USE OF WHILE LOOP TO CHECK FOR DEADLOCK/CREATE CHILD PROCESSES
     */
    int j = 0;
     while(1){
        srand(time(NULL));
        float r;
        r = (float) rand() / RAND_MAX;
        pid_t bus = getpid();
         if(r < p){
             checkDeadlock();
         } else if(directions[i] != NULL){
            //else if theres still buses to be created else continue
            //after continue sleep(2)
             //create child processes
             if(fork() == 0){
                execlp("bus", direction[i], len, bus);
                j++;
             }
         } else {
            continue;
         }
        sleep(2);
     }
     return 0;
}
