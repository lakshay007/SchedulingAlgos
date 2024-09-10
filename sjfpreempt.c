#include <stdio.h>
#include <limits.h>

struct Process {
    int pid;               // Process ID
    int arrival_time;      // Arrival time of the process
    int burst_time;        // Burst time of the process
    int remaining_time;    // Remaining time of the process
    int completion_time;   // Completion time of the process
    int waiting_time;      // Waiting time of the process
    int turnaround_time;   // Turnaround time of the process
};

void calculateTimes(struct Process proc[], int n) {
    int complete = 0, t = 0, minm = INT_MAX;
    int shortest = 0, finish_time;
    int check = 0;
    int total_waiting_time = 0, total_turnaround_time = 0;

    // Initialize remaining time for each process
    for (int i = 0; i < n; i++) {
        proc[i].remaining_time = proc[i].burst_time;
    }

    // Loop until all processes are complete
    while (complete != n) {
        // Find the process with the shortest remaining time that has arrived
        for (int j = 0; j < n; j++) {
            if ((proc[j].arrival_time <= t) && (proc[j].remaining_time < minm) && proc[j].remaining_time > 0) {
                minm = proc[j].remaining_time;
                shortest = j;
                check = 1;
            }
        }

        // If no process is found, increment the time
        if (check == 0) {
            t++;
            continue;
        }

        // Reduce the remaining time of the shortest process
        proc[shortest].remaining_time--;

        // Update minimum remaining time
        minm = proc[shortest].remaining_time;
        if (minm == 0)
            minm = INT_MAX;

        // If a process gets fully executed
        if (proc[shortest].remaining_time == 0) {
            complete++;
            check = 0;
            finish_time = t + 1;

            // Calculate waiting time and turnaround time
            proc[shortest].waiting_time = finish_time - proc[shortest].burst_time - proc[shortest].arrival_time;

            // In case a process has a negative waiting time, make it zero
            if (proc[shortest].waiting_time < 0)
                proc[shortest].waiting_time = 0;

            proc[shortest].turnaround_time = finish_time - proc[shortest].arrival_time;
            proc[shortest].completion_time = finish_time;

            total_waiting_time += proc[shortest].waiting_time;
            total_turnaround_time += proc[shortest].turnaround_time;
        }

        // Increment the time
        t++;
    }

    // Display the results
    printf("PID\tArrival\tBurst\tCompletion\tTurnaround\tWaiting\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t\t%d\t\t%d\n", proc[i].pid, proc[i].arrival_time, proc[i].burst_time, proc[i].completion_time, proc[i].turnaround_time, proc[i].waiting_time);
    }

    printf("\nAverage Waiting Time: %.2f\n", (float)total_waiting_time / n);
    printf("Average Turnaround Time: %.2f\n", (float)total_turnaround_time / n);
}

int main() {
    int n;

    // Take number of processes as input
    printf("Enter number of processes: ");
    scanf("%d", &n);

    struct Process proc[n];

    // Input process details
    for (int i = 0; i < n; i++) {
        proc[i].pid = i + 1;
        printf("Enter arrival time and burst time for process %d: ", i + 1);
        scanf("%d %d", &proc[i].arrival_time, &proc[i].burst_time);
    }

    // Call function to calculate and display times
    calculateTimes(proc, n);

    return 0;
}
