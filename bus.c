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

sem_t north, west, south, east, junction, matrix_lock;

//initialize semaphores
 sem_init(&north, 0, 0);
 sem_init(&west, 0, 0);
 sem_init(&south, 0, 0);
 sem_init(&east, 0, 0);
 sem_init(&junction, 0, 0);
 sem_init(&matrix_lock, 0, 0); 



int main(int argc, char* argv[]){
    char direction[100];
    direction = &argv[1];
    int length = strlen(&argv[2]);
    pid_t busId = &argv[3];

    FILE Matrix_file = &argv[4];
    int matrix[][4] = {0};

    for(int i = 0; i < length; i++){
        for(int j = 0; j < 4; j++){
            if(directions[i] == 'N'){
                printf("Bus %d North bus started\n",busId);
                printf("Bus %d West bus started\n",getpid());
                sem_wait(&matrix_lock);
                printf("Bus %d request for North-Lock\n", busId);
                matrix[i][N] = 1;
                fprintf(matrix_file, "%d", matrix[i][N]);//updating the matrix.txt and specific value
                sem_post(&matrix_lock);

                sem_wait(&north);

                sem_wait(&matrix_lock);
                printf("Bus %d North Acquires North-lock\n", busId);
                matrix[i][N] = 2;
                sem_post(&matrix_lock);

                sem_wait(&west);

                sem_wait(&matrix_lock);
                printf("Bus %d request for West-Lock\n", busId);
                matrix[i][W] = 1;
                sem_post(&matrix_lock);

                printf("Bus %d Request Junction-Lock\n", busId);
                sem_wait(&junction);
                printf("Bus %d Acquires Junction-Lock; Passing Junction\n", busId);
                sleep(2);
                sem_post(&junction);
                printf("Bus %d releases Junction-Lock\n", busId);

                sem_post(&west);

                sem_wait(&matrix_lock);
                printf("Bus %d West releases West-lock\n", getpid());
                matrix[i][W] = 0;
                sem_post(&matrix_lock);

                sem_post(&north);

                sem_wait(&matrix_lock);
                printf("Bus %d North releases North-lock\n", getpid());
                matrix[i][N] = 0;
                sem_post(&matrix_lock);

            } else if(directions[i] == 'W'){

                printf("Bus %d West bus started\n",busId);
                printf("Bus %d South bus started\n",getpid());

                sem_wait(&matrix_lock);
                printf("Bus %d request for West-Lock\n", busId);
                matrix[i][W] = 1;
                sem_post(&matrix_lock);

                sem_wait(&west);

                sem_wait(&matrix_lock);
                printf("Bus %d West Acquires West-lock\n", busId);
                matrix[i][W] = 2;
                sem_post(&matrix_lock);

                sem_wait(&south);

                sem_wait(&matrix_lock);
                printf("Bus %d request for South-Lock\n", busId);
                matrix[i][S] = 1;
                sem_post(&matrix_lock);

                printf("Bus %d Request Junction-Lock\n", busId);
                sem_wait(&junction);
                printf("Bus %d Acquires Junction-Lock; Passing Junction\n", busId);
                sleep(2);
                sem_post(&junction);
                printf("Bus %d releases Junction-Lock\n", busId);

                sem_post(&south);

                sem_wait(&matrix_lock);
                printf("Bus %d South releases South-lock\n", getpid());
                matrix[i][S] = 0;
                sem_post(&matrix_lock);

                sem_post(&west);

                sem_wait(&matrix_lock);
                printf("Bus %d West releases West-lock\n", getpid());
                matrix[i][W] = 0;
                sem_post(&matrix_lock);

            } else if(directions[i] == 'S'){

                printf("Bus %d South bus started\n",busId);
                printf("Bus %d East bus started\n",getpid());
                
                sem_wait(&matrix_lock);
                printf("Bus %d request for South-Lock\n", busId);
                matrix[i][S] = 1;
                sem_post(&matrix_lock);

                sem_wait(&south);

                sem_wait(&matrix_lockx);
                printf("Bus %d South Acquires South-lock\n", busId);
                matrix[i][S] = 2;
                sem_post(&matrix_lock);

                sem_wait(&east);

                sem_wait(&matrix_lock);
                printf("Bus %d request for East-Lock\n", busId);
                Matrix[i][E] = 1;
                sem_post(&matrix_lock);

                printf("Bus %d Request Junction-Lock\n", busId);
                sem_wait(&junction);
                printf("Bus %d Acquires Junction-Lock; Passing Junction\n", busId);
                sleep(2);
                sem_post(&junction);
                printf("Bus %d releases Junction-Lock\n", busId);

                sem_post(&east);

                sem_wait(&matrix_lock);
                printf("Bus %d East releases East-lock\n", getpid());
                matrix[i][E] = 0;
                sem_post(&matrix_lock);

                sem_post(&south);

                sem_wait(&matrix_lock);
                printf("Bus %d South releases South-lock\n", getpid());
                matrix[i][S] = 0;
                sem_post(&matrix_lock);
            } else {
                direction[i] = 'E';
                printf("Bus %d East bus started\n",busId);
                printf("Bus %d North bus started\n",getpid());
                
                sem_wait(&matrix_lock);
                printf("Bus %d request for East-Lock\n", busId);
                matrix[i][E] = 1;
                sem_post(&matrix_lock);

                sem_wait(&east);

                sem_wait(&matrix_lock);
                printf("Bus %d East Acquires East-lock\n", busId);
                matrix[i][E] = 2;
                sem_post(&matrix_lock);

                sem_wait(&north);

                sem_wait(&matrix_lock);
                printf("Bus %d request for North-Lock\n", busId);
                Matrix[i][N] = 1;
                sem_post(&matrix_lock);

                printf("Bus %d Request Junction-Lock\n", busId);
                sem_wait(&junction);
                printf("Bus %d Acquires Junction-Lock; Passing Junction\n", busId);
                sleep(2);
                sem_post(&junction);
                printf("Bus %d releases Junction-Lock\n", busId);

                sem_post(&north);

                sem_wait(&matrix_lock);
                printf("Bus %d North releases North-lock\n", getpid());
                matrix[i][N] = 0;
                sem_post(&matrix_lock);

                sem_post(&east);

                sem_wait(&matrix_lock);
                printf("Bus %d East releases East-lock\n", getpid());
                matrix[i][E] = 0;
                sem_post(&matrix_lock);
            }
        }
    }
}
