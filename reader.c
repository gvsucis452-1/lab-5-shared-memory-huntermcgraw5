/**********************************************************
 *
 * reader.c
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

   key_t passkey = ftok("writer.c", 1);

   if((shmId = shmget(passkey, SHM_SIZE, S_IRUSR | S_IWUSR)) < 0) { 
      perror ("Unable to get shared memory\n"); 
      exit (1); 
   }

   if((sharedMemoryPtr = shmat (shmId, 0, 0)) == (void*) -1) { 
      perror ("Unable to attach\n"); 
      exit (1); 
   }
   
   char turn;
   printf("Waiting for writer...\n");
   while(1) {
      turn = sharedMemoryPtr[0];
      while(turn == 'w') {
         turn = sharedMemoryPtr[0];
      }
      printf("Reader Received: %s\n", sharedMemoryPtr + 1);
      strcpy(sharedMemoryPtr, "w");
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

   printf("time to exit\n");
   exit(0);
}
