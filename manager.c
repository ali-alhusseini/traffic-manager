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
#include <fcntl.h>
#include <sys/stat.h>

#define BUFFER 100
#define MAX_SEMAPHORES 4
#define N 0
#define W 1
#define S 2
#define E 3
#define NORTH "/north"
#define WEST "/west"
#define SOUTH "/south"
#define EAST "/east"
#define JUNCTION "/junction"
#define MATRIXLOCK "/matrixLock"
//sem_t north, west, south, east, junction, matrix_lock;

// Global variables
int n_buses = 0;
char buses[BUFFER];
FILE *seq_file, *matrix_file;
int matrix[BUFFER][BUFFER];


/**
 * Checks the matrix in matrix.txt and detects a deadlock.
 */
bool checkDeadlock() {
    int pairs = 0;
    int temp_matrix[n_buses][MAX_SEMAPHORES];
    matrix_file = fopen("matrix.txt", "r");

    // Read matrix from matrix.txt
    for (int i = 0; i < n_buses; i++) {
        for (int j = 0; j < MAX_SEMAPHORES; j++) {
            fscanf(matrix_file, "%d ", &temp_matrix[i][j]);
        }
    }

    // Check for a deadlock 
    for (int i = 0; i < n_buses; i++) {
        for (int j = 0; j < MAX_SEMAPHORES; j++) {
           if(temp_matrix[i][j] == 2 && (temp_matrix[i][j+1] == 1 || temp_matrix[i][j%3] == 1)){
            pairs = pairs + 1;
           }   
      }
    }
    if (pairs == 4) {
        printf("THERE ARE %d PAIRS.\n", pairs);
        printf("Deadlock detected\n");
        return true;
    }
    // for(int i = 0; i < n_buses; i++){
    //     for(int j = 0; j < MAX_SEMAPHORES; j++){
    //         printf("%d ", temp_matrix[i][j]);
    //     }
    //     printf("\n");
    // }
    printf("NO DEADLOCK DETECTED, THERE ARE %d PAIRS.\n", pairs);
    return false; 
}

int main(int argc, char *argv[]) {
    //FILE *matrix_f;
    if (argc == 2) {
        double p = atof(argv[1]);
        if (p >= 0.2 && p <= 0.7) {
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

            //printf("Value: %d\n", n_buses);
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
            //printf("Value: %d", n_buses);
            
            // Create child processes and check for deadlock
            int j = 0;
        while(1) {
            srand(time(NULL));
            double r;
            r = (double) rand() / RAND_MAX;
            //r = 0.8;
            pid_t bus = getpid();
             if(r < p){
                 if(checkDeadlock()){
                    printf("DEADLOCK\n");
                    exit(0);
                 }
             } else if(&buses[j] != NULL && j < n_buses){
                //else if theres still buses to be created else continue
                //after continue sleep(2)
                //create child processes
                char n_buses_str[10];
                sprintf(n_buses_str, "%d", n_buses);
                 if(fork() == 0){
                    char index[10];
                    sprintf(index,"%d", j);
                    printf("%s", index);
                    // char n_buses_str[10];
                    // sprintf(n_buses_str, "%d", n_buses);
                    execlp("./bus3", "bus3", &buses[j], n_buses_str,index, NULL);
                 }
                 j++;
                 p = 1-p;
                 } else if(checkDeadlock()){
                 break;
                }
            sleep(1);
            }
            

            //Close Files
            fclose(seq_file);
            fclose(matrix_file);
            return 0;
        } else {
            printf("Value of p has to be between 0.2 and 0.7\n");
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

