// C program to implement Shortest Remaining Time First
// (SRTF) or Preemptive Shortest Job First (SJF)
// SRTF is a preemptive algorithm, which means that the
// currently running process can be interrupted if a
// new process arrives with a shorter burst time. It is
// a dynamic algorithm and has a low average waiting time.
// Time complexity is O(n) and space complexity is O(n).
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define FALSE 0
#define TRUE  1

struct Process {
	int pid; // Process ID
	int bt; // Burst Time
	int art; // Arrival Time
};

// Function prototypes
void FindWaitingTime(struct Process *,int,int *);
void FindTurnAroundTime(struct Process *,int,int *,int *);
void FindAvgTime(struct Process *, int);


// Function to find the waiting time for all
// processes
void FindWaitingTime(struct  Process proc[], int n,int wt[])
{
	int rt[n];

	// Copy the burst time into rt[]
	for (int i = 0; i < n; i++)
		rt[i] = proc[i].bt;

	int complete = 0, t = 0, minm = INT_MAX;
	int shortest = 0, finish_time;
	int check = FALSE;

	// Process until all processes are
	// completed
	while (complete != n) {

		// Find process with minimum
		// remaining time among the
		// processes that arrive until the
		// current time`
		for (int j = 0; j < n; j++) {
			if ((proc[j].art <= t) &&
			(rt[j] < minm) && rt[j] > 0) {
				minm = rt[j];
				shortest = j;
				check = TRUE;
			}
		}

		if (check == FALSE) {
			t++;
			continue;
		}

		// Reduce remaining time by one
		rt[shortest]--;

		// Update minimum
		minm = rt[shortest];
		if (minm == 0)
			minm = INT_MAX;

		// If a process gets completely
		// executed
		if (rt[shortest] == 0) {

			// Increment complete
			complete++;
			check = FALSE;

			// Find finish time of current
			// process
			finish_time = t + 1;

			// Calculate waiting time
			wt[shortest] = finish_time -
						proc[shortest].bt -
						proc[shortest].art;

			if (wt[shortest] < 0)
				wt[shortest] = 0;
		}
		// Increment time
		t++;
	}
}

// Function to calculate turn around time
void FindTurnAroundTime(struct Process proc[], int n,
						int wt[], int tat[])
{
	// calculating turnaround time by adding
	// bt[i] + wt[i]
	for (int i = 0; i < n; i++)
		tat[i] = proc[i].bt + wt[i];
}

// Function to calculate average time
void FindAvgTime(struct Process proc[], int n)
{
	int wt[n], tat[n], total_wt = 0,
					total_tat = 0;

	// Function to find waiting time of all
	// processes
	FindWaitingTime(proc, n, wt);

	// Function to find turn around time for
	// all processes
	FindTurnAroundTime(proc, n, wt, tat);

	// Display processes along with all
	// details
	printf("P\t\tBT\t\tWT\t\tTAT\t\t\n");

	// Calculate total waiting time and
	// total turnaround time
	for (int i = 0; i < n; i++) {
		total_wt = total_wt + wt[i];
		total_tat = total_tat + tat[i];
		printf("%i", proc[i].pid);
		printf("\t\t %i",proc[i].bt);
		printf("\t\t %i",wt[i]);
		printf("\t\t %i \n", tat[i]);
	}

	printf("\nAverage waiting time = %f", (float)total_wt / (float)n);
	printf("\nAverage turn around time = %f",(float)total_tat / (float)n);
}

// Driver code
int main()
{
	struct Process proc[5] = { { 1, 6, 2 }, { 2, 2, 5 },
					{ 3, 8, 1 }, { 4, 3, 0}, {5, 4, 4} };
	int n = sizeof(proc) / sizeof(proc[0]);

	FindAvgTime(proc, n);
	return 0;
}
