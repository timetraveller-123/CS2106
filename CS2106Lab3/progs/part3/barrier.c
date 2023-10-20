#include <stdio.h>
#include <semaphore.h>
#include <sys/shm.h>

int *count;
sem_t* sem;
int nproc = 0, shmid1, shmid2;
void init_barrier(int numproc) {
  shmid1 = shmget(IPC_PRIVATE, 2*sizeof(sem_t), IPC_CREAT | 0600);
  shmid2 = shmget(IPC_PRIVATE, sizeof(int), IPC_CREAT | 0600);
  sem = (sem_t*)shmat(shmid1, NULL, 0);
  count = (int *)shmat(shmid2, NULL, 0);
  count[0] = 0;
  nproc = numproc;
  sem_init(sem, 1, 1);
  sem_init(sem + 1, 1, 0);
}

void reach_barrier() {
  sem_wait(sem);
  count[0] ++;
  sem_post(sem);

  if(count[0] == nproc) {
    sem_post(sem+1);
  } else {
    sem_wait(sem+1);
    sem_post(sem+1);
  }
}

void destroy_barrier(int my_pid) {
    if(my_pid != 0) {
        // Destroy the semaphores and detach
        // and free any shared memory. Notice
        // that we explicity check that it is
        // the parent doing it.
        sem_destroy(sem);
        sem_destroy(sem+1);
        shmdt(sem);
        shmdt(count);
        shmctl(shmid1, IPC_RMID, NULL);
        shmctl(shmid2, IPC_RMID, NULL);
    }
}


