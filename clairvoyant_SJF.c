/* C implementation of Clairvoyant
   Shortest Job First algorithm.
   Clairvoyant SJF is a theoretical
   concept in which the algorihtm
   looks in the future and waits for
   the shortest process to arrive.
   This results in the least average
   waiting time. The difference between
   Clairvoyant and regular SJF is that
   Clairvoyant can look into the future and wait
   for the shortest process and allocate
   the resource accordingly, whereas
   regular SJF has to allocate the
   resources to the processes that
   have already arrived and are waitingà
   for the ready queue.
*/



#include <stdio.h>
#include <limits.h>

struct Process {
    int pid;
    int arrival_time;
    int burst_time;
};

void findWaiting_Time(struct Process proc[], int n, int wt[]) {
    int remaining_burst_time[n];

    // Initialize remaining burst times
    for(int i=0; i<n; i++)
        remaining_burst_time[i] = proc[i].burst_time;

    int complete = 0;
    int t = 0, min_burst_time = INT_MAX, shortest_job = 0;
    int finish_time;
    int check = 0;

    // Process until all processes are completed
    while(complete != n) {
        // Find process with minimum burst time
        for(int i=0; i<n; i++) {
            if(proc[i].arrival_time <= t && remaining_burst_time[i] < min_burst_time && remaining_burst_time[i] > 0) {
                min_burst_time = remaining_burst_time[i];
                shortest_job = i;
                check = 1;
            }
        }

        if(check == 0) {
            t++;
            continue;
        }

        // Reduce remaining burst time of the selected process
        remaining_burst_time[shortest_job]--;

        // Update minimum burst time
        min_burst_time = remaining_burst_time[shortest_job];
        if(min_burst_time == 0)
            min_burst_time = INT_MAX;

        // If a process is completed
        if(remaining_burst_time[shortest_job] == 0) {
            complete++;
            check = 0;

            finish_time = t + 1;

            // Calculate waiting time
            wt[shortest_job] = finish_time - proc[shortest_job].burst_time - proc[shortest_job].arrival_time;

            if (wt[shortest_job] < 0)
                wt[shortest_job] = 0;
        }

        // Increment time
        t++;
    }
}

void findTurnAroundTime(struct Process proc[], int n, int wt[], int tat[]) {
    // Calculate turn around time using waiting time and burst time
    for (int i = 0; i < n; i++)
        tat[i] = proc[i].burst_time + wt[i];
}

void findAvgTime(struct Process proc[], int n) {
    int wt[n], tat[n], total_wt = 0, total_tat = 0;

    findWaiting_Time(proc, n, wt);
    findTurnAroundTime(proc, n, wt, tat);

    printf("Process\tBurst Time\tWaiting Time\tTurnaround Time\n");

    // Calculate total waiting time and total turn around time
    for (int i = 0; i < n; i++) {
        total_wt = total_wt + wt[i];
        total_tat = total_tat + tat[i];

        printf("%d\t%d\t\t%d\t\t%d\n", proc[i].pid, proc[i].burst_time, wt[i], tat[i]);
    }

    printf("Average waiting time: %.2f\n", (float) total_wt / n);
    printf("Average turnaround time: %.2f\n", (float) total_tat / n);
}

int main() {
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    struct Process proc[n];

    // Input process details
    for(int i=0; i<n; i++) {
        printf("Enter arrival time for process %d: ", i+1);
        scanf("%d", &proc[i].arrival_time);

        printf("Enter burst time for process %d: ", i+1);
        scanf("%d", &proc[i].burst_time);

        proc[i].pid = i + 1;
    }

    findAvgTime(proc, n);

    return 0;
}
