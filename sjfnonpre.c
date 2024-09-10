#include <stdio.h>

struct Process {
    int id;
    int arrival_time;
    int burst_time;
    int wait_time;
    int turnaround_time;
    int completion_time;
};

void sortByArrivalTime(struct Process proc[], int n) {
    struct Process temp;
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (proc[i].arrival_time > proc[j].arrival_time) {
                temp = proc[i];
                proc[i] = proc[j];
                proc[j] = temp;
            }
        }
    }
}

void calculateWaitAndTurnaroundTime(struct Process proc[], int n) {
    int current_time = 0;  // Tracks the current time in the simulation
    int completed = 0;
    int is_completed[n];   // To track which processes are completed

    for (int i = 0; i < n; i++) {
        is_completed[i] = 0;
    }

    while (completed != n) {
        int idx = -1;
        int min_burst_time = 100000; // Some large value

        for (int i = 0; i < n; i++) {
            // Find the process with the shortest burst time that has arrived and is not completed
            if (proc[i].arrival_time <= current_time && is_completed[i] == 0) {
                if (proc[i].burst_time < min_burst_time) {
                    min_burst_time = proc[i].burst_time;
                    idx = i;
                }
            }
        }

        if (idx != -1) {
            proc[idx].completion_time = current_time + proc[idx].burst_time;
            proc[idx].turnaround_time = proc[idx].completion_time - proc[idx].arrival_time;
            proc[idx].wait_time = proc[idx].turnaround_time - proc[idx].burst_time;

            current_time = proc[idx].completion_time;
            is_completed[idx] = 1;
            completed++;
        } else {
            current_time++; // If no process is available, increment the time
        }
    }
}

void displayProcesses(struct Process proc[], int n) {
    float total_wait_time = 0, total_turnaround_time = 0;
    printf("Process\tArrival Time\tBurst Time\tWait Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++) {
        total_wait_time += proc[i].wait_time;
        total_turnaround_time += proc[i].turnaround_time;
        printf("P%d\t%d\t\t%d\t\t%d\t\t%d\n", proc[i].id, proc[i].arrival_time, proc[i].burst_time, proc[i].wait_time, proc[i].turnaround_time);
    }

    printf("\nAverage Wait Time: %.2f\n", total_wait_time / n);
    printf("Average Turnaround Time: %.2f\n", total_turnaround_time / n);
}

int main() {
    int n;

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    struct Process proc[n];

    for (int i = 0; i < n; i++) {
        proc[i].id = i + 1;
        printf("Enter arrival time and burst time for process P%d: ", proc[i].id);
        scanf("%d%d", &proc[i].arrival_time, &proc[i].burst_time);
    }

    sortByArrivalTime(proc, n);
    calculateWaitAndTurnaroundTime(proc, n);
    displayProcesses(proc, n);

    return 0;
}
