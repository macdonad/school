#include <unistd.h> 
#include <sys/types.h> 
#include <sys/wait.h> 
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/types.h> 
#include <sys/ipc.h> 
#include <sys/sem.h>
#include <errno.h>
#include <string.h>
#include <stdio.h>

union semun {
  int val;
};

int main(void) {
  union semun sem_val;
  int sem_id = semget (IPC_PRIVATE, 1, 00600);
  
  sem_val.val = 0;
  int i;
  
  for (i = 0; i < 100000; i++) {
    sem_val.val++;
    if (semctl(sem_id, 0, SETVAL, sem_val) == -1) { 
      printf("%d\n", sem_val.val);
      break;
    }
	  
  }
  semctl(sem_id, 0, IPC_RMID);
  return 0;
}
