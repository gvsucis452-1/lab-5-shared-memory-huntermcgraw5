Hunter McGraw

1. What exactly is being output by Sample Program 1 (i.e. what is the meaning of the output values)?

The program output: Value a: 0x7385860de000  Value b: 0x7385860df000

The meaning of value a is the address of the start of the shared memory space. The value of b is the address of the end of the shared memory space since its the value of a plus SHM_SIZE.

2. Read the man pages; then describe the meaning / purpose of each argument used by the shmget() function call.

IPC_PRIVATE - The argument that is used to create a new shared memory segment.
SHM_SIZE - Specifies the size of the shared memory segment rounded up to a multiple of PAGE_SIZE.
IPC_CREAT|S_IRUSR|S_IWUSR - These are all flags. IPC_CREAT creates a new segment rather than looking for a segment. S_IRUSR gives read access, S_IWUSR gives write access.

3. Describe two specific uses of the shmctl() function call

shmctl() can destroy the shared memory segment by using the IPC_RMID argument. It can also lock and unlock the shared memory segment with the args SHM_LOCK and SHM_UNLOCK.

4. Read the man pages, then use shmctl() to modify Sample Program 1 so that it prints out the size of the shared memory segment

See sampleProgram1.c

5. Submit your screenshots

   <img width="795" height="315" alt="image" src="https://github.com/user-attachments/assets/ae8eaf8f-77e5-4ce2-b70b-8fbbe9d1d828" />

<img width="809" height="217" alt="image" src="https://github.com/user-attachments/assets/54016568-9796-4114-80b7-1897d0399d09" />
