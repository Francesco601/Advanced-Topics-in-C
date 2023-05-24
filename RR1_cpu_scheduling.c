// C program  implementation of Round Robin (RR) CPU scheduling
// algorithm. Round Robin approach generally focuses on Time Sharing
// techniques. The period of time for which a process is allowed to
// run in this pre-emptive method is called the "time quantum."
// Each process or job present in the ready queue is assigned the
// CPU for the time quantum. If the exectuion of the process
// is completed during that time, then the process will end. If not,
// the process will go back to the waiting table and wait for its
// next turn to finish execution. The RR algorithm can be implemented
// for processes that all have the same arrival time (=0) or for
// processes that have different arrival times. This program implements
// the case of same arrival times.



#include<stdio.h>
#include<stdlib.h>

//function prototypes
void findWaitingTime(int *,int,int *,int *, int);
void findTurnAroundTime(int *,int,int *,int *,int *);
void findavgTime(int *,int,int *,int);
#define TRUE 1
#define FALSE 0


// Function to find the waiting time for all
// processes
void findWaitingTime(int processes[], int n,
			int bt[], int wt[], int quantum)
{
	// Make a copy of burst times bt[] to store remaining
	// burst times.
	int rem_bt[n];
	for (int i = 0 ; i < n ; i++)
		rem_bt[i] = bt[i];

	int t = 0; // Current time

	// Keep traversing processes in round robin manner
	// until all of them are not done.
	while (1)
	{
		int  done = TRUE;

		// Traverse all processes one by one repeatedly
		for (int i = 0 ; i < n; i++)
		{
			// If burst time of a process is greater than 0
			// then only need to process further
			if (rem_bt[i] > 0)
			{
				done = FALSE; // There is a pending process

				if (rem_bt[i] > quantum)
				{
					// Increase the value of t i.e. shows
					// how much time a process has been processed
					t += quantum;

					// Decrease the burst_time of current process
					// by quantum
					rem_bt[i] -= quantum;
				}

				// If burst time is smaller than or equal to
				// quantum. Last cycle for this process
				else
				{
					// Increase the value of t i.e. shows
					// how much time a process has been processed
					t = t + rem_bt[i];

					// Waiting time is current time minus time
					// used by this process
					wt[i] = t - bt[i];

					// As the process gets fully executed
					// make its remaining burst time = 0
					rem_bt[i] = 0;
				}
			}
		}

		// If all processes are done
		if (done == TRUE)
		break;
	}
}

// Function to calculate turn around time
void findTurnAroundTime(int processes[], int n,
						int bt[], int wt[], int tat[])
{
	// calculating turnaround time by adding
	// bt[i] + wt[i]
	for (int i = 0; i < n ; i++)
		tat[i] = bt[i] + wt[i];
}

// Function to calculate average time
void findavgTime(int processes[], int n, int bt[],int quantum)
{
	int wt[n], tat[n], total_wt = 0, total_tat = 0;

	findWaitingTime(processes, n, bt, wt, quantum);
	findTurnAroundTime(processes, n, bt, wt, tat);

	// Display processes along with all details
	printf("PN\t BT\t");
        printf("WT \t TAT");
      
	// Calculate total waiting time and total turn
	// around time
	for (int i=0; i<n; i++)
	{
		total_wt = total_wt + wt[i];
		total_tat = total_tat + tat[i];
		printf(" %d  \t %d \t %d \t %d\n", i+1,bt[i], wt[i],tat[i]);
	}

	       printf("\nAverage waiting time = %f", (float)total_wt / (float)n);
	       printf("\nAverage turn around time = %f",(float)total_tat / (float)n);
}

// Driver code
int main()
{
	// process id's
	int processes[] = { 1, 2, 3};
	int n = sizeof processes / sizeof processes[0];

	// Burst time of all processes
	int burst_time[] = {10, 5, 8};

	// Time quantum
	int quantum = 2;
	findavgTime(processes, n, burst_time, quantum);
	return 0;
}
