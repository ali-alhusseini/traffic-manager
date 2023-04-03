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
#include <fcntl.h>

#define N 0
#define W 1
#define S 2
#define E 3
#define BUFFER 100
#define MAX_SEMAPHORES 4

// Global Variables
int n_buses = 0;
int matrix[BUFFER][BUFFER];
FILE *matrix_file;

/**
 * Reads the matrix from matrix.txt and saves it.
 */
void readMatrix() {
    matrix_file = fopen("matrix.txt", "r");
    for (int i = 0; i < n_buses; i++) {
        for (int j = 0; j < MAX_SEMAPHORES; j++) {
            fscanf(matrix_file, "%d", &matrix[i][j]);
        }
    }
}

/**
 * Writes the modified matrix to matrix.txt
 */
void writeMatrix() {
    matrix_file = fopen("matrix.txt", "w");
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
    n_buses = atoi(argv[2]);

    // Initialize semaphores
    sem_t* north = sem_open("/north", O_CREAT | O_EXCL, 0644, 1);
    sem_t* west = sem_open("/west", O_CREAT | O_EXCL, 0644, 1);
    sem_t* south = sem_open("/south", O_CREAT | O_EXCL, 0644, 1);
    sem_t* east = sem_open("/east", O_CREAT | O_EXCL, 0644, 1);
    sem_t* junction = sem_open("/junction", O_CREAT | O_EXCL, 0644, 1);
    sem_t* matrix_lock = sem_open("/matrix_lock", O_CREAT | O_EXCL, 0644, 1);

    readMatrix();

    for(int i = 0; i < n_buses; i++) {
        if (direction[i] == 'N') {
            printf("Bus %d: North bus started.\n", getpid());
            // printf("Bus %d: West bus started.\n", getpid());

            printf("Bus %d: Request for North Lock.\n", getpid());
            sem_wait(matrix_lock);
            readMatrix();
            matrix[i][N] = 1;
            writeMatrix();
            sem_post(matrix_lock);

            sem_wait(north);
            printf("Bus %d: North Acquires North Lock.\n", getppid());

            sem_wait(matrix_lock);
            readMatrix();
            matrix[i][N] = 2;
            writeMatrix();
            sem_post(matrix_lock);

            printf("Bus %d: Request for West Lock.\n", getpid());
            sem_wait(matrix_lock);
            writeMatrix();
            matrix[i][W] = 1;
            writeMatrix();
            sem_post(matrix_lock);

            sem_wait(west);
            printf("Bus %d: West Acquires West Lock.\n", getppid());

            sem_wait(matrix_lock);
            readMatrix();
            matrix[i][W] = 2;
            writeMatrix();
            sem_post(matrix_lock);

            printf("Bus %d: Requests Junction Lock.\n", getpid());
            sem_wait(junction);
            printf("Bus %d: Acquires Junction-Lock; Passing Junction\n", getpid());
            sleep(2);
            sem_post(junction);
            printf("Bus %d: releases Junction Lock.\n", getpid());

            sem_post(west);
            printf("Bus %d releases West Lock.\n", getpid());

            sem_wait(matrix_lock);
            readMatrix();
            matrix[i][W] = 0;
            writeMatrix();
            sem_post(matrix_lock);

            sem_post(north);
            printf("Bus %d: releases North Lock.\n", getpid());

            sem_wait(matrix_lock);
            readMatrix();
            matrix[i][N] = 0;
            writeMatrix();
            sem_post(matrix_lock);
        } 
        else if (direction[i] == 'W') {
            printf("Bus %d: West bus started.\n", getpid());
            // printf("Bus %d: South bus started.\n", getpid());

            printf("Bus %d: Request for West Lock.\n", getpid());
            sem_wait(matrix_lock);
            readMatrix();
            matrix[i][W] = 1;
            writeMatrix();
            sem_post(matrix_lock);

            sem_wait(west);
            printf("Bus %d: West Acquires North Lock.\n", getppid());

            sem_wait(matrix_lock);
            readMatrix();
            matrix[i][W] = 2;
            writeMatrix();
            sem_post(matrix_lock);

            printf("Bus %d: Request for South Lock.\n", getpid());
            sem_wait(matrix_lock);
            writeMatrix();
            matrix[i][S] = 1;
            writeMatrix();
            sem_post(matrix_lock);

            sem_wait(south);
            printf("Bus %d: South Acquires South Lock.\n", getppid());

            sem_wait(matrix_lock);
            readMatrix();
            matrix[i][S] = 2;
            writeMatrix();
            sem_post(matrix_lock);

            printf("Bus %d: Requests Junction Lock.\n", getpid());
            sem_wait(junction);
            printf("Bus %d: Acquires Junction-Lock; Passing Junction.\n", getpid());
            sleep(2);
            sem_post(junction);
            printf("Bus %d: releases Junction Lock.\n", getpid());

            sem_post(south);
            printf("Bus %d releases South Lock.\n", getpid());

            sem_wait(matrix_lock);
            readMatrix();
            matrix[i][S] = 0;
            writeMatrix();
            sem_post(matrix_lock);

            sem_post(west);
            printf("Bus %d: releases West Lock.\n", getpid());

            sem_wait(matrix_lock);
            readMatrix();
            matrix[i][W] = 0;
            writeMatrix();
            sem_post(matrix_lock);
        }
        else if (direction[i] == 'S') {
            printf("Bus %d: South bus started.\n", getpid());
            // printf("Bus %d: East bus started.\n", getpid());

            printf("Bus %d: Request for South Lock.\n", getpid());
            sem_wait(matrix_lock);
            readMatrix();
            matrix[i][S] = 1;
            writeMatrix();
            sem_post(matrix_lock);

            sem_wait(south);
            printf("Bus %d: South Acquires South Lock.\n", getppid());

            sem_wait(matrix_lock);
            readMatrix();
            matrix[i][S] = 2;
            writeMatrix();
            sem_post(matrix_lock);

            printf("Bus %d: Request for East Lock.\n", getpid());
            sem_wait(matrix_lock);
            writeMatrix();
            matrix[i][E] = 1;
            writeMatrix();
            sem_post(matrix_lock);

            sem_wait(east);
            printf("Bus %d: East Acquires East Lock.\n", getppid());

            sem_wait(matrix_lock);
            readMatrix();
            matrix[i][E] = 2;
            writeMatrix();
            sem_post(matrix_lock);

            printf("Bus %d: Requests Junction Lock.\n", getpid());
            sem_wait(junction);
            printf("Bus %d: Acquires Junction-Lock; Passing Junction\n", getpid());
            sleep(2);
            sem_post(junction);
            printf("Bus %d: releases Junction Lock.\n", getpid());

            sem_post(east);
            printf("Bus %d releases East Lock.\n", getpid());

            sem_wait(matrix_lock);
            readMatrix();
            matrix[i][E] = 0;
            writeMatrix();
            sem_post(matrix_lock);

            sem_post(south);
            printf("Bus %d: releases South Lock.\n", getpid());

            sem_wait(matrix_lock);
            readMatrix();
            matrix[i][S] = 0;
            writeMatrix();
            sem_post(matrix_lock);
        }
        else {
            printf("Bus %d: East bus started.\n", getpid());
            // printf("Bus %d: North bus started.\n", getpid());

            printf("Bus %d: Request for East Lock.\n", getpid());
            sem_wait(matrix_lock);
            readMatrix();
            matrix[i][E] = 1;
            writeMatrix();
            sem_post(matrix_lock);

            sem_wait(east);
            printf("Bus %d: East Acquires East Lock.\n", getppid());

            sem_wait(matrix_lock);
            readMatrix();
            matrix[i][E] = 2;
            writeMatrix();
            sem_post(matrix_lock);

            printf("Bus %d: Request for North Lock.\n", getpid());
            sem_wait(matrix_lock);
            writeMatrix();
            matrix[i][N] = 1;
            writeMatrix();
            sem_post(matrix_lock);

            sem_wait(north);
            printf("Bus %d: North Acquires North Lock\n", getppid());

            sem_wait(matrix_lock);
            readMatrix();
            matrix[i][N] = 2;
            writeMatrix();
            sem_post(matrix_lock);

            printf("Bus %d: Requests Junction Lock.\n", getpid());
            sem_wait(junction);
            printf("Bus %d: Acquires Junction-Lock; Passing Junction.\n", getpid());
            sleep(2);
            sem_post(junction);
            printf("Bus %d: releases Junction Lock.\n", getpid());

            sem_post(north);
            printf("Bus %d: releases North Lock.\n", getpid());

            sem_wait(matrix_lock);
            readMatrix();
            matrix[i][N] = 0;
            writeMatrix();
            sem_post(matrix_lock);

            sem_post(east);
            printf("Bus %d: releases East Lock.\n", getpid());

            sem_wait(matrix_lock);
            readMatrix();
            matrix[i][E] = 0;
            writeMatrix();
            sem_post(matrix_lock);
        }
    }
    // Close Files and Semaphores
    fclose(matrix_file);
    sem_close(north);
    sem_unlink("/north");
    sem_close(south);
    sem_unlink("/south");
    sem_close(west);
    sem_unlink("/west");
    sem_close(east);
    sem_unlink("/east");
    sem_close(junction);
    sem_unlink("/junction");
    sem_close(matrix_lock);
    sem_unlink("/matrix_lock");
    return 0;
}
