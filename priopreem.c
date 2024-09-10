#include <stdio.h>

struct process {
    int id;       // Process ID
    int at;       // Arrival time
    int bt;       // Burst time
    int bt_remaining; // Remaining burst time (for preemption)
    int priority; // Priority of the process (lower number = higher priority)
    int ct;       // Completion time
    int tt;       // Turnaround time
    int wt;       // Waiting time
    int finished; // Whether the process is finished
};

void calculateTimes(int n, struct process proc[]) {
    int time = 0, completed = 0, min_priority, index;
    
    while (completed != n) {
        min_priority = 10000;
        index = -1;

        // Find the process with the highest priority (lowest priority number) that has arrived
        for (int i = 0; i < n; i++) {
            if (proc[i].at <= time && proc[i].finished == 0 && proc[i].priority < min_priority) {
                min_priority = proc[i].priority;
                index = i;
            }
        }

        if (index != -1) {
            proc[index].bt_remaining--;
            time++;

            // If the process is finished, calculate completion, turnaround, and waiting times
            if (proc[index].bt_remaining == 0) {
                proc[index].finished = 1;
                proc[index].ct = time;
                proc[index].tt = proc[index].ct - proc[index].at;
                proc[index].wt = proc[index].tt - proc[index].bt;
                completed++;
            }
        } else {
            // If no process is available, increment time
            time++;
        }
    }
}

void displayProcesses(struct process proc[], int n) {
    float total_wait_time = 0, total_turnaround_time = 0;

    printf("Process\tArrival Time\tBurst Time\tPriority\tWait Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++) {
        total_wait_time += proc[i].wt;
        total_turnaround_time += proc[i].tt;
        printf("P%d\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", proc[i].id, proc[i].at, proc[i].bt, proc[i].priority, proc[i].wt, proc[i].tt);
    }

    printf("\nAverage Wait Time: %.2f\n", total_wait_time / n);
    printf("Average Turnaround Time: %.2f\n", total_turnaround_time / n);
}

int main() {
    int n;

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    struct process proc[n];

    // Input process details
    for (int i = 0; i < n; i++) {
        proc[i].id = i + 1;
        printf("Enter arrival time, burst time, and priority for process P%d: ", proc[i].id);
        scanf("%d%d%d", &proc[i].at, &proc[i].bt, &proc[i].priority);
        proc[i].bt_remaining = proc[i].bt;  // Initialize remaining burst time
        proc[i].finished = 0;               // Initialize process as not finished
    }

    // Calculate times using Preemptive Priority Scheduling
    calculateTimes(n, proc);

    // Display the results
    displayProcesses(proc, n);

    return 0;
}
