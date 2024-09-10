#include <stdio.h>
#include <stdbool.h>

struct Process {
    int id;
    int arrival_time;
    int burst_time;
    int remaining_time;  // Remaining burst time
    int wait_time;
    int turnaround_time;
};

// Function to calculate waiting and turnaround times
void calculateWaitAndTurnaroundTime(struct Process proc[], int n, int time_quantum) {
    int current_time = 0;  // Tracks the current time
    int completed = 0;     // Number of processes completed
    int queue[100];          // Queue to store the indices of ready processes
    int front = 0, rear = 0;
    bool visited[n];       // To track if a process has been added to the queue

    for (int i = 0; i < n; i++) {
        proc[i].remaining_time = proc[i].burst_time;
        proc[i].wait_time = 0;
        proc[i].turnaround_time = 0;
        visited[i] = false;
    }

    // Add the first process (that arrives at time 0 or earlier) to the queue
    for (int i = 0; i < n; i++) {
        if (proc[i].arrival_time <= current_time) {
            queue[rear++] = i;
            visited[i] = true;
        }
    }

    while (completed != n) {
        if (front != rear) {  // Check if the queue is not empty
            int idx = queue[front++];
            
            if (proc[idx].remaining_time <= time_quantum) {
                current_time += proc[idx].remaining_time;
                proc[idx].remaining_time = 0;
                proc[idx].turnaround_time = current_time - proc[idx].arrival_time;
                proc[idx].wait_time = proc[idx].turnaround_time - proc[idx].burst_time;
                completed++;
            } else {
                current_time += time_quantum;
                proc[idx].remaining_time -= time_quantum;
            }

            // Add new processes that have arrived by the current time to the queue
            for (int i = 0; i < n; i++) {
                if (!visited[i] && proc[i].arrival_time <= current_time) {
                    queue[rear++] = i;
                    visited[i] = true;
                }
            }

            // If the process isn't done, push it back to the queue
            if (proc[idx].remaining_time > 0) {
                queue[rear++] = idx;
            }
        } else {
            // If no process is available, increment time until a process arrives
            current_time++;
            for (int i = 0; i < n; i++) {
                if (!visited[i] && proc[i].arrival_time <= current_time) {
                    queue[rear++] = i;
                    visited[i] = true;
                }
            }
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
    int n, time_quantum;

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    struct Process proc[n];

    for (int i = 0; i < n; i++) {
        proc[i].id = i + 1;
        printf("Enter arrival time and burst time for process P%d: ", proc[i].id);
        scanf("%d%d", &proc[i].arrival_time, &proc[i].burst_time);
    }

    printf("Enter the time quantum: ");
    scanf("%d", &time_quantum);

    calculateWaitAndTurnaroundTime(proc, n, time_quantum);
    displayProcesses(proc, n);

    return 0;
}
