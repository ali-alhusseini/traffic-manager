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
#include <sys/stat.h>

// Constants
#define N 0
#define W 1
#define S 2
#define E 3
#define BUFFER 100
#define MAX_SEMAPHORES 4

// Semaphores
sem_t* n;
sem_t* w; 
sem_t* s;
sem_t* e; 
sem_t* j;
sem_t* m;

// Global variables
int n_buses = 0;
int matrix[BUFFER][BUFFER];
FILE *matrix_file;

void readMatrix();
void writeMatrix();
void printMatrix();

int main(int argc, char* argv[]) {
    char* direction = argv[1];
    n_buses = atoi(argv[2]);
    int i = atoi(argv[3]);
    int num;

    // Open the semaphores
    n = sem_open("/N", O_CREAT, 0644, 1);
    w = sem_open("/W", O_CREAT, 0644, 1);
    s = sem_open("/S", O_CREAT, 0644, 1);
    e = sem_open("/E", O_CREAT, 0644, 1);
    j = sem_open("/J", O_CREAT, 0644, 1);
    m = sem_open("/M", O_CREAT, 0644, 1);

    readMatrix();
    int d = 0;
    // Convert the direction into a number
    char D[2] = {*direction};
    d = strtol(D, NULL, 36) -10;

    /**
     * Convert each direction into a number
     * From the man page for strtol: 
     * The letter A in either upper or lower case represents 10
     * The letter B represents 11 and so on with Z repesenting 35
    */
    char nn = 'N';
    char NN[2] = {nn};
    int numN = strtol(NN, NULL, 36) - 10;

    char ww = 'W';
    char WW[2] = {ww};
    int numW = strtol(WW, NULL, 36) - 10;

    char ss = 'S';
    char SS[2] = {ss};
    int numS = strtol(SS, NULL, 36) - 10;

    char ee = 'E';
    char EE[2] = {ee};
    int numE = strtol(EE, NULL, 36) - 10;

    if (d == numN) {
        printf("Bus <%d>: North bus started.\n", getpid());
        printf("Bus <%d>: Request for North-Lock.\n", getpid());
        sem_wait(n);
        printf("Bus <%d>: Acquires North-Lock.\n", getpid());
        sem_wait(m);
        readMatrix();
        matrix[i][N] = 2;
        writeMatrix();
        sem_post(m);
        printf("Bus <%d>: Request for West-Lock.\n", getppid());
        sem_wait(m);
        readMatrix();
        matrix[i][W] = 1;
        writeMatrix();
        sem_post(m);
        sem_wait(w);
        printf("Bus <%d>: Acquires West-Lock.\n", getppid());
        printf("Bus <%d>: Requests Junction-Lock.\n", getpid());
        sem_wait(j);
        printf("Bus <%d>: Acquires Junction-Lock; Passing Junction\n", getpid());
        sleep(2);
        sem_post(j);
        printf("Bus <%d>: releases Junction-Lock.\n", getpid());
        sem_post(w);
        printf("Bus <%d> releases West-Lock.\n", getppid());
        sem_post(n);
        printf("Bus <%d>: releases North-Lock.\n", getpid());
    } else if (d == numW) {
        printf("Bus <%d>: West bus started.\n", getpid());
        printf("Bus <%d>: Request for West-Lock.\n", getpid());
        sem_wait(w);
        printf("Bus <%d>: Acquires West Lock.\n", getpid());
        sem_wait(m);
        readMatrix();
        matrix[i][W] = 2;
        writeMatrix();
        sem_post(m);
        printf("Bus <%d>: Request for South Lock.\n", getppid());
        sem_wait(m);
        readMatrix();
        matrix[i][S] = 1;
        writeMatrix();
        sem_post(m);
        sem_wait(s);
        printf("Bus <%d>: Acquires South-Lock.\n", getppid());
        printf("Bus <%d>: Requests Junction-Lock.\n", getpid());
        sem_wait(j);
        printf("Bus <%d>: Acquires Junction-Lock; Passing Junction.\n", getpid());
        sleep(2);
        sem_post(j);
        printf("Bus <%d>: releases Junction-Lock.\n", getpid());
        sem_post(s);
        printf("Bus <%d>: releases South-Lock.\n", getppid());
        sem_post(w);
        printf("Bus <%d>: releases West-Lock.\n", getpid());
    } else if (d == numS) {
        printf("Bus <%d>: South bus started.\n", getpid());
        printf("Bus <%d>: Request for South-Lock.\n", getpid());
        sem_wait(s);
        printf("Bus <%d>: Acquires South-Lock.\n", getpid());
        sem_wait(m);
        readMatrix();
        matrix[i][S] = 2;
        writeMatrix();
        sem_post(m);
        printf("Bus <%d>: Request for East-Lock.\n", getppid());
        sem_wait(m);
        readMatrix();
        matrix[i][E] = 1;
        writeMatrix();
        sem_post(m);
        sem_wait(e);
        printf("Bus <%d>: Acquires East-Lock.\n", getppid());
        printf("Bus <%d>: Requests Junction-Lock.\n", getpid());
        sem_wait(j);
        printf("Bus <%d>: Acquires Junction-Lock; Passing Junction\n", getpid());
        sleep(2);
        sem_post(j);
        printf("Bus <%d>: releases Junction-Lock.\n", getpid());
        sem_post(e);
        printf("Bus <%d>: releases East-Lock.\n", getppid());
        sem_post(s);
        printf("Bus <%d>: releases South-Lock.\n", getpid());
    } else if(d == numE) {
        printf("Bus <%d>: East bus started.\n", getpid());
        printf("Bus <%d>: Request for East-Lock.\n", getpid());
        sem_wait(e);
        printf("Bus <%d>: Acquires East-Lock.\n", getpid());
        sem_wait(m);
        readMatrix();
        matrix[i][E] = 2;
        writeMatrix();
        sem_post(m);
        printf("Bus <%d>: Request for North-Lock.\n", getppid());
        sem_wait(m);
        readMatrix();
        matrix[i][N] = 1;
        writeMatrix();
        sem_post(m);
        sem_wait(n);
        printf("Bus <%d>: Acquires North-Lock\n", getppid());
        printf("Bus <%d>: Requests Junction-Lock.\n", getpid());
        sem_wait(j);
        printf("Bus <%d>: Acquires Junction-Lock; Passing Junction.\n", getpid());
        sleep(2);
        sem_post(j);
        printf("Bus <%d>: releases Junction-Lock.\n", getpid());
        sem_post(n);
        printf("Bus <%d>: releases North-Lock.\n", getppid());
        sem_post(e);
        printf("Bus <%d>: releases East-Lock.\n", getpid());
    } else {
        printf("Bus %d: Invalid direction.\n", getpid());
    }
    // Close all semaphores
    sem_close(n);
    sem_unlink("/N");
    sem_close(w);
    sem_unlink("/W");
    sem_close(s);
    sem_unlink("/S");
    sem_close(e);
    sem_unlink("/E");
    sem_close(j);
    sem_unlink("/J");
    sem_close(m);
    sem_unlink("/M");
    return 0;
}

/**
 * Reads the matrix from matrix.txt and saves it.
 */
void readMatrix() {
    matrix_file = fopen("matrix.txt", "r");
    for (int i = 0; i < n_buses; i++) {
        for (int j = 0; j < MAX_SEMAPHORES; j++) {
            fscanf(matrix_file, "%d ", &matrix[i][j]);
        }
    }
    fclose(matrix_file);
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
    fclose(matrix_file); 
}

/**
 * Prints the matrix to the console.
*/
void printMatrix() {
    for (int i = 0; i < n_buses; i++) {
        for (int j = 0; j < MAX_SEMAPHORES; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }  
}
