#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include <pthread.h>
#include <semaphore.h>

#define NUM_PROCESSES 5

int main() {

    int i, j, pid;
    int shmid = shmget(IPC_PRIVATE, 5*sizeof(sem_t), IPC_CREAT | 0600);
    sem_t* sem = (sem_t*)shmat(shmid, NULL, 0);
    for(int i = 1; i<5; i++)
      sem_init(sem+i, 1, 0);
    sem_init(sem, 1, 1);
    
    for(i=0; i<NUM_PROCESSES; i++)
    {
        if((pid = fork()) == 0) {
            break;
        }
    }

    if(pid == 0) {
        sem_wait(sem+i);
        printf("I am child %d\n", i);

        for(j = i*10; j<i*10 + 10; j++){
            printf("%d ", j);
            fflush(stdout);
            usleep(250000);
        }

        printf("\n\n");
        if(i<4)
          sem_post(sem+i+1);
        shmdt(sem);
    }
    else {
        for(i=0; i<NUM_PROCESSES; i++) 
            wait(NULL);
        for(int i = 0; i<5; i++) 
            sem_destroy(sem+i);
        shmdt(sem);
        shmctl(shmid, IPC_RMID, NULL);
    }

}

