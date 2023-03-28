#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <semaphore.h>
#include <stdarg.h>
#include <math.h>
#include <time.h>

#define N 0
#define W 1
#define S 2
#define E 3

sem_t North, West, South, East, Junction, Matrix;

//initialize semaphores
int sem_init(North, 0, 0);
int sem_init(West, 0, 0);
int sem_init(South, 0, 0);
int sem_init(East, 0, 0);
int sem_init(Junction, 0, 0);
int sem_init(Matrix, 0, 0); 
char dir[] = {'North', 'West', 'South', 'East'};


int main(int argc, char* argv[]){
    char direction[100];
    direction = &argv[1];
    int length = &argv[2];
    pid_t busId = &argv[3];

    for(int i = 0; i < length; i++){
        for(int j = 0; j < 4; j++){
            if(directions[i] == 'N'){
                printf("Bus %d %c bus started\n",busId, dir[N]);
                printf("Bus %d %c bus started\n",getpid(), dir[W]);
                sem_wait(&Matrix);
                printf("Bus %d request for %c-Lock\n", busId, dir[N]);
                matrix[i][j] = 1;
                sem_post(&Matrix);

                sem_wait(&North);

                sem_wait(&Matrix);
                printf("Bus %d %c Acquires %c-lock\n", busId, dir[N]);
                matrix[i][j] = 2;
                sem_post(&Matrix);

                sem_wait(&West);

                sem_wait(&Matrix);
                printf("Bus %d Requests for %c-lock\n", getpid(), dir[W]);
                Matrix[i][W] = 1
                sem_post(&Matrix);

                printf("Bus %d Request Junction-Lock\n", busId);
                sem_wait(&Junction);
                printf("Bus %d Acquires Junction-Lock; Passing Junction\n");
                sem_post(&Junction);
                printf("Bus %d releases Junction-Lock\n", busId);

                sem_post(&West);

                sem_wait(&Matrix);
                printf("Bus %d %c releases %c-lock\n", getpid(), dir[W]);
                matrix[i][W] = 0;
                sem_post(&Matrix);

                sem_post(&North);

                sem_wait(&Matrix);
                printf("Bus %d %c Releases %c-lock\n", busId, dir[N]);
                matrix[i][N] = 0;
                sem_post(&Matrix);

            } else if(directions[i] == 'W'){

                printf("Bus %d %c bus started\n",busId, dir[W]);
                printf("Bus %d %c bus started\n",getpid(), dir[S]);

                sem_wait(&Matrix);
                printf("Bus %d request for %c-Lock\n", busId, dir[W]);
                matrix[i][W] = 1;
                sem_post(&Matrix);

                sem_wait(&West);

                sem_wait(&Matrix);
                printf("Bus %d %c Acquires %c-lock\n", busId, dir[W]);
                matrix[i][W] = 2;
                sem_post(&Matrix);

                sem_wait(&South);

                sem_wait(&Matrix);
                printf("Bus %d Requests for %c-lock\n", getpid(), dir[S]);
                Matrix[i][S] = 1
                sem_post(&Matrix);

                printf("Bus %d Request Junction-Lock\n", busId);
                sem_wait(&Junction);
                printf("Bus %d Acquires Junction-Lock; Passing Junction\n");
                sem_post(&Junction);
                printf("Bus %d releases Junction-Lock\n", busId);

                sem_post(&South);

                sem_wait(&Matrix);
                printf("Bus %d %c releases %c-lock\n", getpid(), dir[S]);
                matrix[i][S] = 0;
                sem_post(&Matrix);

                sem_post(&West);

                sem_wait(&Matrix);
                printf("Bus %d %c Releases %c-lock\n", busId, dir[W]);
                matrix[i][W] = 0;
                sem_post(&Matrix);

            } else if(directions[i] == 'S'){

                printf("Bus %d %c bus started\n",busId, dir[S]);
                printf("Bus %d %c bus started\n",getpid(), dir[E]);
                
                sem_wait(&Matrix);
                printf("Bus %d request for %c-Lock\n", busId, dir[S]);
                matrix[i][S] = 1;
                sem_post(&Matrix);

                sem_wait(&South);

                sem_wait(&Matrix);
                printf("Bus %d %c Acquires %c-lock\n", busId, dir[S]);
                matrix[i][S] = 2;
                sem_post(&Matrix);

                sem_wait(&East);

                sem_wait(&Matrix);
                printf("Bus %d Requests for %c-lock\n", getpid(), dir[E]);
                Matrix[i][E] = 1
                sem_post(&Matrix);

                printf("Bus %d Request Junction-Lock\n", busId);
                sem_wait(&Junction);
                printf("Bus %d Acquires Junction-Lock; Passing Junction\n");
                sem_post(&Junction);
                printf("Bus %d releases Junction-Lock\n", busId);

                sem_post(&East);

                sem_wait(&Matrix);
                printf("Bus %d %c releases %c-lock\n", getpid(), dir[E]);
                matrix[i][E] = 0;
                sem_post(&Matrix);

                sem_post(&South);

                sem_wait(&Matrix);
                printf("Bus %d %c Releases %c-lock\n", busId, dir[S]);
                matrix[i][S] = 0;
                sem_post(&Matrix);
            } else {
                direction[i] = 'E';
                printf("Bus %d %c bus started\n",busId, dir[E]);
                printf("Bus %d %c bus started\n",getpid(), dir[N]);
                
                sem_wait(&Matrix);
                printf("Bus %d request for %c-Lock\n", busId, dir[E]);
                matrix[i][E] = 1;
                sem_post(&Matrix);

                sem_wait(&East);

                sem_wait(&Matrix);
                printf("Bus %d %c Acquires %c-lock\n", busId, dir[E]);
                matrix[i][E] = 2;
                sem_post(&Matrix);

                sem_wait(&North);

                sem_wait(&Matrix);
                printf("Bus %d Requests for %c-lock\n", getpid(), dir[N]);
                Matrix[i][N] = 1
                sem_post(&Matrix);

                printf("Bus %d Request Junction-Lock\n", busId);
                sem_wait(&Junction);
                printf("Bus %d Acquires Junction-Lock; Passing Junction\n");
                sem_post(&Junction);
                printf("Bus %d releases Junction-Lock\n", busId);

                sem_post(&North);

                sem_wait(&Matrix);
                printf("Bus %d %c releases %c-lock\n", getpid(), dir[N]);
                matrix[i][N] = 0;
                sem_post(&Matrix);

                sem_post(&East);

                sem_wait(&Matrix);
                printf("Bus %d %c Releases %c-lock\n", busId, dir[E]);
                matrix[i][E] = 0;
                sem_post(&Matrix);
            }
        }
    }
}