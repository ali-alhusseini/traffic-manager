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

// Constants
#define BUFFER 100
#define MAX_SEMAPHORES 4
#define N 0
#define W 1
#define S 2
#define E 3

// Global variables
int n_buses = 0;
char buses[BUFFER];
FILE *seq_file, *matrix_file;
int matrix[BUFFER][BUFFER];

char* dir[] = {"North", "West", "South", "East"};

bool checkDeadlock();
void readSequence();
void writeMatrix();

int main(int argc, char *argv[]) {
    if (argc == 2) {
        double p = atof(argv[1]);
        if (p >= 0.2 && p <= 0.7) {
            // Read sequence and create matrix
            readSequence();
            writeMatrix();

            // Create child processes and check for deadlock
            int j = 0;
            int signal = 0;
            while (1) {
                srand(time(NULL));
                double r = (double)rand() / RAND_MAX;
                if (r < p) {
                    if (checkDeadlock()) {
                        signal++;
                        printf("System Deadlocked.\n");
                        printf("Program now terminating.\n");
                        printf("Press enter to continue...");
                        getchar();
                        exit(0);
                    } else {
                        if (&buses[j] != NULL && j < n_buses && signal == 0) {
                            char n_buses_str[10];
                            sprintf(n_buses_str, "%d", n_buses);
                            if (fork() == 0) {
                                char index[10];
                                sprintf(index, "%d", j);
                                printf("%s", index);
                                execlp("./bus2", "bus2", &buses[j], n_buses_str, index, NULL);
                            } else {
                                wait(NULL);
                            }
                        }
                    j++;
                    }
                }
                sleep(1);
            }
        } else {
            printf("Invalid probability value. Please enter a value between 0.2 and 0.7.\n");
            printf("Program now terminating.\n");
            printf("Press enter to continue...");
            getchar();
        }
    } else {
        printf("Invalid number of arguments. Please enter a probability value.\n");
        printf("Program now terminating.\n");
        printf("Press enter to continue...");
        getchar();
    }
    return 0;
}


/**
 * Checks the matrix in matrix.txt and detects a deadlock.
 */
bool checkDeadlock()
{
    int pairs = 0;
    int temp_matrix[n_buses][MAX_SEMAPHORES];
    matrix_file = fopen("matrix.txt", "r");
    int visited[n_buses][MAX_SEMAPHORES];

    // Read matrix from matrix.txt
    for (int i = 0; i < n_buses; i++) {
        for (int j = 0; j < MAX_SEMAPHORES; j++) {
            fscanf(matrix_file, "%d ", &temp_matrix[i][j]);
        }
    }

    // Check for a deadlock
    int x = 0;
    for (int i = 0; i < n_buses; i++) {
        for (int j = 0; j < MAX_SEMAPHORES; j++) {
            if (temp_matrix[i][j] == 2 && (temp_matrix[i][j + 1] == 1 || temp_matrix[i][j % 3] == 1)) {
                if(temp_matrix[i][j] == 2 && temp_matrix[i][j + 1] == 1){
                visited[i][j] = 2;
                visited[i][j+1] = 1;
                pairs++;
                } else if (temp_matrix[i][j] == 2 && temp_matrix[i][j % 3] == 1) {
                visited[i][j] = 2;
                visited[i][j%3] = 1;
                pairs++;
                } else {
                    break;
                }
            }
        }
    }
    if (pairs == 4) {
        printf("THERE ARE %d PAIRS.\n", pairs);
        printf("Deadlock detected\n");
        printf("Cycle:\n");
        for (int i = 0; i < 4; i++) {
                if(visited[i][0] == 2 && visited[i][1] == 1){
                printf("---> Bus from %s is waiting for bus from %s ---> \n", dir[0], dir[1]);
                } else if (visited[i][1] == 2 && visited[i][2] == 1){
                   printf("---> Bus from %s is waiting for bus from %s ---> \n", dir[1], dir[2]); 
                } else if (visited[i][2] == 2 && visited[i][3] == 1){
                   printf("---> Bus from %s is waiting for bus from %s ---> \n", dir[2], dir[3]); 
                } else if (visited[i][3] == 2 && visited[i][0] == 1){
                   printf("---> Bus from %s is waiting for bus from %s ---> \n", dir[3], dir[0]); 
                } else {
                    break;
                }
    }
    return true;
    }
    return false;
}

/**
 * Read sequence from sequence.txt file.
 */
void readSequence() {
    seq_file = fopen("sequence.txt", "r");
    if (seq_file == NULL) {
        printf("Error opening file sequence.txt\n");
    }

    // Determine the number of characters in sequence.txt
    while (fscanf(seq_file, "%c", &buses[n_buses]) != EOF) {
        n_buses++;
    }

    // Save characters to character array "buses"
    int i = 0;
    char ch;
    while ((ch = fgetc(seq_file)) != EOF) {
        buses[i] = ch;
        i++;
    }

    // Print the number of buses and the sequence of buses
    printf("Number of buses: %d\n", n_buses);
    printf("Sequence of Buses: ");
    for (int i = 0; i < n_buses; i++) {
        printf("%c ", buses[i]);
    }
    printf("\n");
    fclose(seq_file);
}

/**
 * Write matrix to file matrix.txt.
 */
void writeMatrix() {
    matrix_file = fopen("matrix.txt", "w");
    if (matrix_file == NULL) {
        printf("Coudln't open file matrix.txt\n");
    }

    for (int i = 0; i < n_buses; i++) {
        for (int j = 0; j < MAX_SEMAPHORES; j++) {
            fprintf(matrix_file, "%d ", matrix[i][j]);
        }
        fprintf(matrix_file, "\n");
    }
    fclose(matrix_file);
}
