#include <stdio.h>
#define MAX_PROCESS 100

typedef struct {
    int pronum;
    int arrivalTime;
    int burstTime;
    int waitingTime;
    int turnaroundTime;
    int completionTime;
} Process;
void calculateFCFS(Process processes[], int n) {
    int i;
    int totalWaitingTime = 0;
    int totalTurnaroundTime = 0;
    
    for(int i = 0;i<n;i++){
    for(int j = 0;j<n-i-1;j++){
    if(processes[j].arrivalTime>processes[j+1].arrivalTime){
    Process temp = processes[j];
    processes[j] = processes[j+1];
    processes[j+1] = temp;
    }
    
    }
    }
    processes[0].completionTime = processes[0].arrivalTime + processes[0].burstTime;
    processes[0].turnaroundTime = processes[0].completionTime - processes[0].arrivalTime;
    processes[0].waitingTime = processes[0].turnaroundTime - processes[0].burstTime;
    totalWaitingTime += processes[0].waitingTime;
    totalTurnaroundTime += processes[0].turnaroundTime;
    for (i = 1; i < n; i++) {
    
        processes[i].completionTime = processes[i - 1].completionTime + processes[i].burstTime;
    
        processes[i].turnaroundTime = processes[i].completionTime - processes[i].arrivalTime;
        processes[i].waitingTime = processes[i].turnaroundTime - processes[i].burstTime;
        totalWaitingTime += processes[i].waitingTime;
        totalTurnaroundTime += processes[i].turnaroundTime;
    }
  
    printf("\nProcess\tArrival Time\tBurst Time\tWaiting Time\tTurnaround Time\tCompletion Time\n");
    for (i = 0; i < n; i++) {
        printf("%d\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n",
               processes[i].pronum, processes[i].arrivalTime, processes[i].burstTime,
               processes[i].waitingTime, processes[i].turnaroundTime,
               processes[i].completionTime);
    }
    printf("\nAverage Waiting Time: %.2f\n", (float)totalWaitingTime / n);
    printf("Average Turnaround Time: %.2f\n", (float)totalTurnaroundTime / n);
}
int main() {
    Process processes[MAX_PROCESS];
    int n, i;
  
    printf("Enter the number of processes: ");
    scanf("%d", &n);
   
    for (i = 0; i < n; i++) {
        printf("Enter arrival time and burst time for process %d: ", i + 1);
        scanf("%d %d", &processes[i].arrivalTime, &processes[i].burstTime);
        processes[i].pronum = i+1;
    }
    
    calculateFCFS(processes, n);
    return 0;
}