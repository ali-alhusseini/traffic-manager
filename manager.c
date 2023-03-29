#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <semaphore.h>
#include <stdarg.h>
#include <math.h>
#include <time.h>

#define MAX_BUSES 100 // Maximum number of buses
#define MAX_SEMAPHORES 4 // Number of synchronizing semaphores

// Change flag to 1 if there's deadlock
int checkDeadlock(); 
int matrix[][MAX_SEMAPHORES] = {0};

int main(int argc, char *argv[]) {
    if (argc == 2) {
        double p = atof(argv[1]);

        if (p >= 0 && p <= 1) {
            FILE *seq_file, *matrix_file;
            char buses[MAX_BUSES];
            int n_buses = 0; // Number of buses in sequence.txt

            // Read the number of buses from the sequence.txt file
            seq_file = fopen("sequence.txt", "r");
            if (seq_file == NULL) {
                printf("Couldn't open file sequence.txt\n");
                return 1;
            }
            while (fscanf(seq_file, "%c", &buses[n_buses]) != EOF) {
                n_buses++;
            }

            int i = 0;
            char ch;
            while ((ch = fgetc(seq_file)) != EOF) {
                buses[i] = ch;
                i++;
            }

            // Create the matrix.txt file and initialize the matrix to 0
            matrix_file = fopen("matrix.txt", "w");
            if (matrix_file == NULL) {
                printf("Error creating file matrix.txt\n");
                return 1;
            }
            for (int i = 0; i < n_buses; i++) {
                for (int j = 0; j < MAX_SEMAPHORES; j++) {
                    fprintf(matrix_file, "%d ", matrix[i][j]);
                }
                fprintf(matrix_file, "\n");
            }

            // USE OF WHILE LOOP TO CHECK FOR DEADLOCK/CREATE CHILD PROCESSES
            int j = 0;
            while(1) {
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
                        execlp("bus", buses[j], buses[n_buses], bus);
                        j++;
                     }
                 } else {
                    continue;
                }
            sleep(2);
            }

            //Close Files
            fclose(seq_file);
            fclose(matrix_file);
            return 0;
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
     return 0;
}