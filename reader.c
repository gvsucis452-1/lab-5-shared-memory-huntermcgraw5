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

char *sharedMemoryPtr, temp[128];
int shmId, count; 

int main () 
{ 

   int fd[2];
   int pipe_creation_result;

   pipe_creation_result = pipe(fd);

   if (pipe_creation_result < 0) {
      perror("Failed pipe creation\n");
      exit(1);
   }
   int output = 0;
   int input;
   write(fd[1], &output, sizeof(int));

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
   output = 1;
   printf("Waiting for writer...\n");
   while(1) {
      sleep(random() % 4 + 1);
      while(sharedMemoryPtr[0] == 'w');
      printf("Reader Received: %s\n", sharedMemoryPtr + 1);
      strcpy(temp, "1");
      strcat(temp, sharedMemoryPtr + 1);
      read(fd[0], &input, sizeof(int));
      while(input == 1) {
         read(fd[0], &input, sizeof(int));
      }
      write(fd[1], &output, sizeof(int));
      if (sharedMemoryPtr[0] == 'r') {
         strcpy(sharedMemoryPtr, temp);
         while(sharedMemoryPtr[0] == '1');
      } else {
         strcpy(sharedMemoryPtr, "w");
      }
      output = 0;
      write(fd[1], &output, sizeof(int));
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

