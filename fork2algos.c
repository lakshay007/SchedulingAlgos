#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

struct Process {
    int id;
    int arrival_time;
    int burst_time;
    int wait_time;
    int turnaround_time;
};

// Function to perform Round Robin scheduling
void roundRobin(struct Process proc[], int n, int time_quantum) {
    int remaining_burst[n];
    int wait_time = 0, turnaround_time = 0;
    int completed = 0, current_time = 0;

    for (int i = 0; i < n; i++) {
        remaining_burst[i] = proc[i].burst_time;
    }

    while (completed != n) {
        for (int i = 0; i < n; i++) {
            if (proc[i].arrival_time <= current_time && remaining_burst[i] > 0) {
                if (remaining_burst[i] <= time_quantum) {
                    current_time += remaining_burst[i];
                    remaining_burst[i] = 0;
                    completed++;

                    proc[i].turnaround_time = current_time - proc[i].arrival_time;
                    proc[i].wait_time = proc[i].turnaround_time - proc[i].burst_time;
                } else {
                    current_time += time_quantum;
                    remaining_burst[i] -= time_quantum;
                }
            }
        }
    }

    // Display Round Robin results
    printf("\nParent Process (Round Robin Scheduling):\n");
    printf("Process\tArrival Time\tBurst Time\tWait Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++) {
        wait_time += proc[i].wait_time;
        turnaround_time += proc[i].turnaround_time;
        printf("P%d\t%d\t\t%d\t\t%d\t\t%d\n", proc[i].id, proc[i].arrival_time, proc[i].burst_time, proc[i].wait_time, proc[i].turnaround_time);
    }
    printf("Average Wait Time: %.2f\n", (float)wait_time / n);
    printf("Average Turnaround Time: %.2f\n", (float)turnaround_time / n);
}

// Function to perform FCFS scheduling
void fcfs(struct Process proc[], int n) {
    int wait_time = 0, turnaround_time = 0;
    int current_time = 0;

    for (int i = 0; i < n; i++) {
        if (current_time < proc[i].arrival_time) {
            current_time = proc[i].arrival_time;  // Wait for process to arrive
        }

        proc[i].wait_time = current_time - proc[i].arrival_time;
        proc[i].turnaround_time = proc[i].wait_time + proc[i].burst_time;
        current_time += proc[i].burst_time;
    }

    // Display FCFS results
    printf("\nChild Process (FCFS Scheduling):\n");
    printf("Process\tArrival Time\tBurst Time\tWait Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++) {
        wait_time += proc[i].wait_time;
        turnaround_time += proc[i].turnaround_time;
        printf("P%d\t%d\t\t%d\t\t%d\t\t%d\n", proc[i].id, proc[i].arrival_time, proc[i].burst_time, proc[i].wait_time, proc[i].turnaround_time);
    }
    printf("Average Wait Time: %.2f\n", (float)wait_time / n);
    printf("Average Turnaround Time: %.2f\n", (float)turnaround_time / n);
}

int main() {
    int n, time_quantum;

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    struct Process proc[n];
    struct Process proc_copy[n];

    for (int i = 0; i < n; i++) {
        proc[i].id = i + 1;
        printf("Enter arrival time and burst time for process P%d: ", proc[i].id);
        scanf("%d%d", &proc[i].arrival_time, &proc[i].burst_time);
        proc_copy[i] = proc[i];  // Copying data for child process (FCFS)
    }

    printf("Enter the time quantum for Round Robin: ");
    scanf("%d", &time_quantum);

    pid_t pid = fork();  // Create a child process

    if (pid == 0) {
        // Child process - FCFS scheduling
        fcfs(proc_copy, n);
    } else if (pid > 0) {
        // Parent process - Round Robin scheduling
        wait(NULL);  // Wait for the child process to finish
        roundRobin(proc, n, time_quantum);
    } else {
        printf("Fork failed!\n");
    }

    return 0;
}
