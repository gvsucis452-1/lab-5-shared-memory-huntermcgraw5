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

#define SHM_SIZE 4096

int main () 
{ 
   int shmId; 
   char *sharedMemoryPtr;
   char turn = sharedMemoryPtr[0];
   struct shmid_ds shmid_struct;
   key_t passkey;
   passkey = ftok("/home/mcgrawh/Documents/cis452/lab-5-shared-memory-huntermcgraw5/writer.c", 1);
   printf("%d\n", passkey);
   
   if((shmId = shmget(passkey, SHM_SIZE, S_IRUSR | S_IWUSR)) < 0) { 
      perror ("Unable to get shared memory\n"); 
      exit (1); 
   }

   if((sharedMemoryPtr = shmat (shmId, 0, 0)) == (void*) -1) { 
      perror ("Unable to attach\n"); 
      exit (1); 
   }



   while(1) {
      printf("waiting\n");
      while(turn == 'w');
      printf("Reader Received: %s\n", sharedMemoryPtr);
      strcpy(sharedMemoryPtr, "w");
   }




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

