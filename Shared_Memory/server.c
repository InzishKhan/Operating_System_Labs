#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include<stdlib.h>
#include<string.h>
#define SHM_KEY 1234
#define SHM_SIZE 1024
int main() {
   int shmid;
   char *shared_memory;
   // Get the shared memory segment
   shmid = shmget(SHM_KEY, SHM_SIZE, 0666);
   if (shmid < 0) {
     perror("shmget");
     return 1;
    }
    // Attach shared memory segment
    shared_memory = (char *)shmat(shmid, NULL, 0);
    if (shared_memory == (char *)(-1)) {
      perror("shmat");
      return 1;
    }
    int sum = 0;
    int total = 0;
    char *tok = strtok(shared_memory, " ");
    while (tok != NULL) {
       sum=sum+ atoi(tok);
       total++;
       tok = strtok(NULL, " ");
    
    }
    
    float avg=0;
    avg=sum/total;
    printf("Sum = %d\n", sum);
    printf("Average = %f\n",avg);

    // Detach shared memory segment
    if (shmdt(shared_memory) == -1) {
       perror("shmdt");
       return 1;
     }
     // Delete shared memory segment
    if (shmctl(shmid, IPC_RMID, NULL) == -1) {
      perror("shmctl");
      return 1;
    }
  return 0;
}
