#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <semaphore.h>
#include <stdarg.h>
#include <math.h>
#include <time.h>
#include <string.h>

#define N 0
#define W 1
#define S 2
#define E 3
#define BUFFER 100
#define MAX_SEMAPHORES 4

//initialize semaphores
sem_t north, west, south, east, junction, matrix_lock;
sem_init(&north, 0, 1);
sem_init(&west, 0, 1);
sem_init(&south, 0, 1);
sem_init(&east, 0, 1);
sem_init(&junction, 0, 1);
sem_init(&matrix_lock, 0, 1); 

// Global Variables
int n_buses = 0;
int matrix[BUFFER][BUFFER];

/**
 * Writes the modified matrix to matrix.txt
 */
void writeMatrix(FILE* matrix_file) {
    for (int i = 0; i < n_buses; i++) {
        for (int j = 0; j < MAX_SEMAPHORES; j++) {
            fprintf(matrix_file, "%d ", matrix[i][j]);
        }
        fprintf(matrix_file, "\n");
    }  
}

int main(int argc, char* argv[]){
    char* direction = argv[1];
    // char *n_buses_str = argv[2];

    // Read the matrix from file and save it
    FILE* matrix_file = fopen("matrix.txt", "r");
    n_buses = atoi(argv[2]);

    for (int i = 0; i < n_buses; i++) {
        for (int j = 0; j < MAX_SEMAPHORES; j++) {
            fscanf(matrix_file, "%d", &matrix[i][j]);
        }
    }

    for(int i = 0; i < n_buses; i++) {
        for(int j = 0; j < MAX_SEMAPHORES; j++){
            if(directions[i] == 'N'){
                printf("Bus %d North bus started\n",getppid());
                printf("Bus %d West bus started\n",getpid());

                sem_wait(&matrix_lock);
                printf("Bus %d request for North-Lock\n", getppid());
                fscanf(matrix_file, "%d", &matrix[i][N]);
                matrix[i][N] = 1;
                writeMatrix(matrix_file);
                fprintf(matrix_file, "%d", matrix[i][N]);//updating the matrix.txt and specific value
                sem_post(&matrix_lock);

                sem_wait(&north);

                sem_wait(&matrix_lock);
                printf("Bus %d North Acquires North-lock\n", getppid());
                fscanf(matrix_file, "%d", &matrix[i][N]);
                matrix[i][N] = 2;
                writeMatrix(matrix_file);
                fprintf(matrix_file, "%d", matrix[i][N]);
                sem_post(&matrix_lock);

                sem_wait(&west);

                sem_wait(&matrix_lock);
                printf("Bus %d request for West-Lock\n", getpid());
                fscanf(matrix_file, "%d", &matrix[i][W]);
                matrix[i][W] = 1;
                writeMatrix(matrix_file);
                fprintf(matrix_file, "%d", matrix[i][W]);
                sem_post(&matrix_lock);

                printf("Bus %d Request Junction-Lock\n", getppid());
                sem_wait(&junction);
                printf("Bus %d Acquires Junction-Lock; Passing Junction\n", getppid());
                sleep(2);
                sem_post(&junction);
                printf("Bus %d releases Junction-Lock\n", getppid());

                sem_post(&west);

                sem_wait(&matrix_lock);
                printf("Bus %d West releases West-lock\n", getpid());
                fscanf(matrix_file, "%d", &matrix[i][W]);
                matrix[i][W] = 0;
                writeMatrix(matrix_file);
                fprintf(matrix_file, "%d", matrix[i][W]);
                sem_post(&matrix_lock);

                sem_post(&north);

                sem_wait(&matrix_lock);
                printf("Bus %d North releases North-lock\n", getppid());
                fscanf(matrix_file, "%d", &matrix[i][N]);
                matrix[i][N] = 0;
                writeMatrix(matrix_file);
                fprintf(matrix_file, "%d", matrix[i][N]);
                sem_post(&matrix_lock);

            } else if(directions[i] == 'W'){

                printf("Bus %d West bus started\n",getppid());
                printf("Bus %d South bus started\n",getpid());

                sem_wait(&matrix_lock);
                printf("Bus %d request for West-Lock\n", getppid());
                fscanf(matrix_file, "%d", &matrix[i][W]);
                matrix[i][W] = 1;
                writeMatrix(matrix_file);
                fprintf(matrix_file, "%d", matrix[i][W]);
                sem_post(&matrix_lock);

                sem_wait(&west);

                sem_wait(&matrix_lock);
                printf("Bus %d West Acquires West-lock\n", getppid());
                fscanf(matrix_file, "%d", &matrix[i][W]);
                matrix[i][W] = 2;
                writeMatrix(matrix_file);
                fprintf(matrix_file, "%d", matrix[i][W]);
                sem_post(&matrix_lock);

                sem_wait(&south);

                sem_wait(&matrix_lock);
                printf("Bus %d request for South-Lock\n", getpid());
                fscanf(matrix_file, "%d", &matrix[i][S]);
                matrix[i][S] = 1;
                writeMatrix(matrix_file);
                fprintf(matrix_file, "%d", matrix[i][S]);
                sem_post(&matrix_lock);

                printf("Bus %d Request Junction-Lock\n", getppid());
                sem_wait(&junction);
                printf("Bus %d Acquires Junction-Lock; Passing Junction\n", busId);
                sleep(2);
                sem_post(&junction);
                printf("Bus %d releases Junction-Lock\n", getppid());

                sem_post(&south);

                sem_wait(&matrix_lock);
                printf("Bus %d South releases South-lock\n", getpid());
                fscanf(matrix_file, "%d", &matrix[i][S]);
                matrix[i][S] = 0;
                writeMatrix(matrix_file);
                fprintf(matrix_file, "%d", matrix[i][S]);
                sem_post(&matrix_lock);

                sem_post(&west);

                sem_wait(&matrix_lock);
                printf("Bus %d West releases West-lock\n", getppid());
                fscanf(matrix_file, "%d", &matrix[i][W]);
                matrix[i][W] = 0;
                writeMatrix(matrix_file);
                fprintf(matrix_file, "%d", matrix[i][W]);
                sem_post(&matrix_lock);

            } else if(directions[i] == 'S'){

                printf("Bus %d South bus started\n",getppid());
                printf("Bus %d East bus started\n",getpid());
                
                sem_wait(&matrix_lock);
                printf("Bus %d request for South-Lock\n", getppid());
                fscanf(matrix_file, "%d", &matrix[i][S]);
                matrix[i][S] = 1;
                writeMatrix(matrix_file);
                fprintf(matrix_file, "%d", matrix[i][S]);
                sem_post(&matrix_lock);

                sem_wait(&south);

                sem_wait(&matrix_lock);
                printf("Bus %d South Acquires South-lock\n", getppid());
                fscanf(matrix_file, "%d", &matrix[i][S]);
                matrix[i][S] = 2;
                writeMatrix(matrix_file);
                fprintf(matrix_file, "%d", matrix[i][S]);
                sem_post(&matrix_lock);

                sem_wait(&east);

                sem_wait(&matrix_lock);
                printf("Bus %d request for East-Lock\n", getpid());
                fscanf(matrix_file, "%d", &matrix[i][E]);
                matrix[i][E] = 1;
                writeMatrix(matrix_file);
                fprintf(matrix_file, "%d", matrix[i][E]);
                sem_post(&matrix_lock);

                printf("Bus %d Request Junction-Lock\n", getppid());
                sem_wait(&junction);
                printf("Bus %d Acquires Junction-Lock; Passing Junction\n", getppid());
                sleep(2);
                sem_post(&junction);
                printf("Bus %d releases Junction-Lock\n", getppid());

                sem_post(&east);

                sem_wait(&matrix_lock);
                printf("Bus %d East releases East-lock\n", getpid());
                fscanf(matrix_file, "%d", &matrix[i][E]);
                matrix[i][E] = 0;
                writeMatrix(matrix_file);
                fprintf(matrix_file, "%d", matrix[i][E]);
                sem_post(&matrix_lock);

                sem_post(&south);

                sem_wait(&matrix_lock);
                printf("Bus %d South releases South-lock\n", getppid());
                fscanf(matrix_file, "%d", &matrix[i][S]);
                matrix[i][S] = 0;
                writeMatrix(matrix_file);
                fprintf(matrix_file, "%d", matrix[i][S]);
                sem_post(&matrix_lock);
            } else {
                direction[i] = 'E';
                printf("Bus %d East bus started\n",getppid());
                printf("Bus %d North bus started\n",getpid());
                
                sem_wait(&matrix_lock);
                printf("Bus %d request for East-Lock\n", getppid());
                fscanf(matrix_file, "%d", &matrix[i][E]);
                matrix[i][E] = 1;
                writeMatrix(matrix_file);
                fprintf(matrix_file, "%d", matrix[i][E]);
                sem_post(&matrix_lock);

                sem_wait(&east);

                sem_wait(&matrix_lock);
                printf("Bus %d East Acquires East-lock\n", getppid());
                fscanf(matrix_file, "%d", &matrix[i][E]);
                matrix[i][E] = 2;
                writeMatrix(matrix_file);
                fprintf(matrix_file, "%d", matrix[i][E]);
                sem_post(&matrix_lock);

                sem_wait(&north);

                sem_wait(&matrix_lock);
                printf("Bus %d request for North-Lock\n", getpid());
                fscanf(matrix_file, "%d", &matrix[i][N]);
                matrix[i][N] = 1;
                writeMatrix(matrix_file);
                fprintf(matrix_file, "%d", matrix[i][N]);
                sem_post(&matrix_lock);

                printf("Bus %d Request Junction-Lock\n", getppid());
                sem_wait(&junction);
                printf("Bus %d Acquires Junction-Lock; Passing Junction\n", getppid());
                sleep(2);
                sem_post(&junction);
                printf("Bus %d releases Junction-Lock\n", getppid());

                sem_post(&north);

                sem_wait(&matrix_lock);
                printf("Bus %d North releases North-lock\n", getpid());
                fscanf(matrix_file, "%d", &matrix[i][N]);
                matrix[i][N] = 0;
                writeMatrix(matrix_file);
                fprintf(matrix_file, "%d", matrix[i][N]);
                sem_post(&matrix_lock);

                sem_post(&east);

                sem_wait(&matrix_lock);
                printf("Bus %d East releases East-lock\n", getppid());
                fscanf(matrix_file, "%d", &matrix[i][E]);
                matrix[i][E] = 0;
                writeMatrix(matrix_file);
                fprintf(matrix_file, "%d", matrix[i][E]);
                sem_post(&matrix_lock);
            }
        }
    }
    // Close Files
    fclose(matrix_file);
}
