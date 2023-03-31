#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <semaphore.h>
#include <stdarg.h>
#include <math.h>
#include <time.h>
#include <stdbool.h>

#define BUFFER 100
#define MAX_SEMAPHORES 4

// Global variables
int n_buses = 0;
char buses[BUFFER];
FILE *seq_file, *matrix_file;
int matrix[][MAX_SEMAPHORES] = {0};

/**
 * Checks the matrix in matrix.txt and detects a deadlock.
 */
bool checkDeadlock() {
    int pairs = 0;
    int temp_matrix[BUFFER][BUFFER];
    matrix_file = fopen("matrix.txt", "r");

    for (int i = 0; i < n_buses; i++) {
        for (int j = 0; j < MAX_SEMAPHORES; j++) {
            fscanf(matrix_file, "%d", &temp_matrix[i][j]);
        }
    }

    for (int i = 0; i < n_buses; i++) {
        for (int j = 0; j < MAX_SEMAPHORES; j++) {
            if (temp_matrix[i][j] == 2 && 
                j < MAX_SEMAPHORES - 1 &&
                temp_matrix[i][j+1] == 1) {
                    pairs++;
                }
        }
    }
}

int main(int argc, char *argv[]) {
    if (argc == 2) {
        double p = atof(argv[1]);
        if (p >= 0 && p <= 1) {
            // Read the number of buses from the sequence.txt file
            seq_file = fopen("sequence.txt", "r");
            if (seq_file == NULL) {
                printf("Error opening file sequence.txt\n");
                return 1;
            }

            // Determine the number of characters in sequence.txt
            while (fscanf(seq_file, "%c", &buses[n_buses]) != EOF) {
                n_buses++;
            }

            // Save characters from sequence.txt to a character array "buses"
            int i = 0;
            char ch;
            while ((ch = fgetc(seq_file)) != EOF) {
                buses[i] = ch;
                i++;
            }

            // Create the matrix.txt file and initialize the matrix to 0
            matrix_file = fopen("matrix.txt", "w");
            if (matrix_file == NULL) {
                printf("Error opening file matrix.txt\n");
                return 1;
            }

            // Write matrix to file matrix.txt
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
                 } else if(buses[j] != NULL){
                    //else if theres still buses to be created else continue
                    //after continue sleep(2)
                     //create child processes
                     if(fork() == 0){
                        char n_buses_str[10];
                        sprintf(n_buses_str, "%d", n_buses);
                        execlp("./bus", "bus", buses[j], n_buses_str, matrix_file, bus, NULL);
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