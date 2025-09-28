/**********************************************************
 *
 * sampleProgram1.c
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

#define SHM_SIZE 4096

int main () 
{ 
   int shmId; 
   char *sharedMemoryPtr;
   struct shmid_ds shmid_struct;
   
   if((shmId = shmget(IPC_PRIVATE, SHM_SIZE, IPC_CREAT|S_IRUSR|S_IWUSR)) < 0) { 
      perror ("Unable to get shared memory\n"); 
      exit (1); 
   } 
   if((sharedMemoryPtr = shmat (shmId, 0, 0)) == (void*) -1) { 
      perror ("Unable to attach\n"); 
      exit (1); 
   }

   printf("Value a: %p\t Value b: %p\n", (void *) sharedMemoryPtr, (void *) sharedMemoryPtr + SHM_SIZE);

   if(shmdt (sharedMemoryPtr) < 0) { 
      perror ("Unable to detach\n"); 
      exit (1); 
   }
   if(shmctl (shmId, IPC_STAT, &shmid_struct) < 0) {
      perror ("Unable to copy information into struct\n");
      exit(1);
   }
   printf("ID: %d\n", shmId);
   printf("Size: %ld\n", shmid_struct.shm_segsz);
   
   pause();


   return 0; 
}
