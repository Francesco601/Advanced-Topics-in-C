/* C program to implement Peterson’s Algorithm
/ for the producer-consumer problem in operating system
 process synchronization. Peterson's algorithm is
 used to synchronize two processes (but can be extended to
 n processes). It uses two key variables, a boolian array
 FLAG of size two and an int variable TURN to acheive
 synchronization. In the solution, i represents the Comsumer
 and j represents the Producer. Initially the flags are set
 to false. When a process wants to execute it's critical
 section, it sets it flag to true and turn to the value of
 the index of  the other process. This means the process
 wants to execute but it will allow the other process to
 tun first. The process performs busy waiting until the
 other process has finished it own critical section.
 After this, the current process enters its critical
 section and adds or removes a random number from the
 shared buffer (queue). After completing the critical
 section, it sets it own flag to false, indicating that
 it does not want to execute anymore. The program runs
 for a fixed amount of time before exiting. This time
 can be changed by changing the value of the constant
 RT. See https://en.wikipedia.org/wiki/Peterson%27s_algorithm.
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdbool.h>
#define _BSD_SOURCE
#include <sys/time.h>


#define BSIZE 8 // Buffer size
#define PWT 2 // Producer wait time limit
#define CWT 10 // Consumer wait time limit
#define RT 10 // Program run-time in seconds

int shmid1, shmid2, shmid3, shmid4; //shared memory ids
key_t k1 = 5491, k2 = 5812, k3 = 4327, k4 = 3213;
bool* SHM1;
int* SHM2;
int* SHM3;

int myrand(int n) // Returns a random number between 1 and n
{
	time_t t;
	srand((unsigned)time(&t));
	return (rand() % n + 1);
}

int main()
      
{      //get shared memory
	shmid1 = shmget(k1, sizeof(bool) * 2, IPC_CREAT | 0660); // flag
	shmid2 = shmget(k2, sizeof(int) * 1, IPC_CREAT | 0660); // turn
	shmid3 = shmget(k3, sizeof(int) * BSIZE, IPC_CREAT | 0660); // buffer
	shmid4 = shmget(k4, sizeof(int) * 1, IPC_CREAT | 0660); // time stamp

	if (shmid1 < 0 || shmid2 < 0 || shmid3 < 0 || shmid4 < 0) {
		perror("Main shmget error: ");
		exit(1);
	}
	SHM3 = (int*)shmat(shmid3, NULL, 0); // assign shared memory resource
	int ix = 0;
	while (ix < BSIZE) // Initializing buffer
		SHM3[ix++] = 0;

	struct timeval t;
	time_t t1, t2;
	gettimeofday(&t, NULL);
	t1 = t.tv_sec;

	int* state = (int*)shmat(shmid4, NULL, 0);
	*state = 1;
	int wait_time;

	int i = 0; // Consumer
	int j = 1; // Producer

	if (fork() == 0) // Producer code
	{
		SHM1 = (bool*)shmat(shmid1, NULL, 0);
		SHM2 = (int*)shmat(shmid2, NULL, 0);
		SHM3 = (int*)shmat(shmid3, NULL, 0);
		if (SHM1 == (bool*)-1 || SHM2 == (int*)-1 || SHM3 == (int*)-1) {
			perror("Producer shmat error: ");
			exit(1);
		}

		bool* flag = SHM1;
		int* turn = SHM2;
		int* buf = SHM3;
		int index = 0;

		while (*state == 1) {
			flag[j] = true;
			printf("Producer is ready now.\n\n");
			*turn = i;
			while (flag[i] == true && *turn == i)
				;

			// Critical Section Begin
			index = 0;
			while (index < BSIZE) {
				if (buf[index] == 0) {
					int tempo = myrand(BSIZE * 3);
					printf("Job %d has been produced\n", tempo);
					buf[index] = tempo;
					break;
				}
				index++;
			}
			if (index == BSIZE)
				printf("Buffer is full, nothing can be produced!!!\n");
			printf("Buffer: ");
			index = 0;
			while (index < BSIZE)
				printf("%d ", buf[index++]);
			printf("\n");
			// Critical Section End

			flag[j] = false;
			if (*state == 0)
				break;
			wait_time = myrand(PWT);
			printf("Producer will wait for %d seconds\n\n", wait_time);
			sleep(wait_time);
		}
		exit(0);
	}

	if (fork() == 0) // Consumer code
	{
		SHM1 = (bool*)shmat(shmid1, NULL, 0);
		SHM2 = (int*)shmat(shmid2, NULL, 0);
		SHM3 = (int*)shmat(shmid3, NULL, 0);
		if (SHM1 == (bool*)-1 || SHM2 == (int*)-1 || SHM3 == (int*)-1) {
			perror("Consumer shmat error:");
			exit(1);
		}

		bool* flag = SHM1;
		int* turn = SHM2;
		int* buf = SHM3;
		int index = 0;
		flag[i] = false;
		sleep(5);
		while (*state == 1) {
			flag[i] = true;
			printf("Consumer is ready now.\n\n");
			*turn = j;
			while (flag[j] == true && *turn == j)
				;

			// Critical Section Begin
			if (buf[0] != 0) {
				printf("Job %d has been consumed\n", buf[0]);
				buf[0] = 0;
				index = 1;
				while (index < BSIZE) // Shifting remaining jobs forward
				{
					buf[index - 1] = buf[index];
					index++;
				}
				buf[index - 1] = 0;
			} else
				printf("Buffer is empty, nothing can be consumed!!!\n");
			printf("Buffer: ");
			index = 0;
			while (index < BSIZE)
				printf("%d ", buf[index++]);
			printf("\n");
			// Critical Section End

			flag[i] = false;
			if (*state == 0)
				break;
			wait_time = myrand(CWT);
			printf("Consumer will sleep for %d seconds\n\n", wait_time);
			sleep(wait_time);
		}
		exit(0);
	}
	// Parent process will now for RT seconds before causing child to terminate
	while (1) {
		gettimeofday(&t, NULL);
		t2 = t.tv_sec;
		if (t2 - t1 > RT) // Program will exit after RT seconds
		{
			*state = 0;
			break;
		}
	}
	// Waiting for both processes to exit

}
