#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <semaphore.h>
#include <stdarg.h>
#include <math.h>
#include <time.h>

#define MAX_SIZE 1000

//Initialize all values to 0
int matrix[][4] = {0}; 

//change flag to 1 if there's deadlock
int checkDeadlock(); 

int main(int argc, char *argv[]) {
    //Probability value
    double p = 0.0;

    if (argc == 2) {
        p = atof(argv[1]);

        if (p >= 0 && p <= 1) {
           FILE* file = fopen("sequence.txt", "r");
           char directions[MAX_SIZE];
           int count = 0;
           if (file == NULL) {
               printf("Couldn't open file sequence.txt\n");
               return 1;
           }
           while (fscanf(file, "%c", &directions[count]) != EOF) {
               count++;
           }
           fclose(file);
        } else {
            printf("Value of p has to be between 0 and 1\n");
            printf("Program now terminating.\n");
            printf("Press enter to continue...");
            getchar();
        }

    } else {
        printf("Missing command line argument.\n");
        printf("Program now terminating.\n");
        printf("Press enter to continue...");
        getchar();
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
         } else if(directions[j] != NULL){
            //else if theres still buses to be created else continue
            //after continue sleep(2)
             //create child processes
             if(fork() == 0){
                execlp("bus", direction[j], len, bus);
                j++;
             }
         } else {
            continue;
         }
        sleep(2);
     }
     return 0;
}
