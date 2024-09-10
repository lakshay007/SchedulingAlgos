#include <stdio.h>

struct Process {
    int pid;
    int arrival_time;
    int burst_time;
    int priority;
    int waiting_time;
    int turnaround_time;
    int completion_time;
    int start_time;
};

void calculateTimes(struct Process proc[], int n) {
    int current_time = 0, completed = 0;
    int total_waiting_time = 0, total_turnaround_time = 0;
    int highest_priority_idx;

    while (completed != n) {
        highest_priority_idx = -1;
        int highest_priority = 9999;

        // Find the highest priority process that has arrived and is not yet completed
        for (int i = 0; i < n; i++) {
            if (proc[i].arrival_time <= current_time && proc[i].completion_time == 0) {
                if (proc[i].priority < highest_priority) {
                    highest_priority = proc[i].priority;
                    highest_priority_idx = i;
                }
            }
        }

        if (highest_priority_idx != -1) {
            proc[highest_priority_idx].start_time = current_time;
            proc[highest_priority_idx].completion_time = current_time + proc[highest_priority_idx].burst_time;
            proc[highest_priority_idx].turnaround_time = proc[highest_priority_idx].completion_time - proc[highest_priority_idx].arrival_time;
            proc[highest_priority_idx].waiting_time = proc[highest_priority_idx].turnaround_time - proc[highest_priority_idx].burst_time;

            total_waiting_time += proc[highest_priority_idx].waiting_time;
            total_turnaround_time += proc[highest_priority_idx].turnaround_time;
            current_time = proc[highest_priority_idx].completion_time;
            completed++;
        } else {
            current_time++;
        }
    }

    // Display results
    printf("PID\tArrival\tBurst\tPriority\tCompletion\tTurnaround\tWaiting\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t\t%d\t\t%d\t\t%d\n", proc[i].pid, proc[i].arrival_time, proc[i].burst_time, proc[i].priority, proc[i].completion_time, proc[i].turnaround_time, proc[i].waiting_time);
    }

    printf("\nAverage Waiting Time: %.2f\n", (float)total_waiting_time / n);
    printf("Average Turnaround Time: %.2f\n", (float)total_turnaround_time / n);
}

int main() {
    int n;
    printf("Enter number of processes: ");
    scanf("%d", &n);

    struct Process proc[n];
    for (int i = 0; i < n; i++) {
        proc[i].pid = i + 1;
        printf("Enter arrival time, burst time, and priority for process %d: ", i + 1);
        scanf("%d %d %d", &proc[i].arrival_time, &proc[i].burst_time, &proc[i].priority);
        proc[i].completion_time = 0;  // Initialize to zero
    }

    calculateTimes(proc, n);

    return 0;
}
