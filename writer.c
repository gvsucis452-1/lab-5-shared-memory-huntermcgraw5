/**********************************************************
 *
 * writer.c
 * CIS 451 Lab 5
 *
 * Hunter McGraw
 *************************************************************/

#include <stdio.h> 
#include <stdlib.h> 
#include <sys/types.h> 
#include <sys/stat.h>
#include <sys/ipc.h> 
#include <sys/shm.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>

#define SHM_SIZE 4096

void sigIntHandler(int);

char *sharedMemoryPtr;
int shmId;

int main () 
{ 
   signal(SIGINT, sigIntHandler);
   
   char input[128];

   key_t passkey = ftok("writer.c", 1);
   
   if((shmId = shmget(passkey, SHM_SIZE, IPC_CREAT|S_IRUSR|S_IWUSR)) < 0) { 
      perror ("Unable to get shared memory\n"); 
      exit (1); 
   } 
   if((sharedMemoryPtr = shmat (shmId, 0, 0)) == (void*) -1) { 
      perror ("Unable to attach\n"); 
      exit (1); 
   }

   strcpy(sharedMemoryPtr, "w");
   char turn;
   while(1) {
       turn = sharedMemoryPtr[0];
<<<<<<< Updated upstream
       while(turn == 'r') {
       	  turn = sharedMemoryPtr[0];
       }
=======
       while(sharedMemoryPtr[0] == 'r' || sharedMemoryPtr[0] == '1');
>>>>>>> Stashed changes
       printf("Input something to write: ");
       scanf("%s", input);
       strcpy(sharedMemoryPtr, "r");
       strcat(sharedMemoryPtr, input);		
   }


   return 0; 
}

void sigIntHandler(int sig_num)
{
   printf(" received an interrupt.\n");

   if(shmdt (sharedMemoryPtr) < 0) { 
      perror ("Unable to detach\n"); 
      exit (1); 
   }

   if(shmctl (shmId, IPC_RMID, 0) < 0) { 
      perror ("Unable to deallocate\n"); 
   }

   printf("time to exit\n");
   exit(0);
}
