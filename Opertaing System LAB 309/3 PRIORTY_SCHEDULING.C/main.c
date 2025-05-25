#include <stdio.h>

struct Process {
    int pid;         
    int burstTime;    
    int priority;    
    int waitingTime;
    int turnaroundTime;
};

void calculateWaitingTime(struct Process proc[], int n) {
    int serviceTime[n];
    serviceTime[0] = 0;
    proc[0].waitingTime = 0;

    for (int i = 1; i < n; i++) {
        serviceTime[i] = serviceTime[i - 1] + proc[i - 1].burstTime;
        proc[i].waitingTime = serviceTime[i] - 0;  // Arrival time assumed 0 for all
        if (proc[i].waitingTime < 0)
            proc[i].waitingTime = 0;
    }
}

void calculateTurnaroundTime(struct Process proc[], int n) {
    for (int i = 0; i < n; i++) {
        proc[i].turnaroundTime = proc[i].burstTime + proc[i].waitingTime;
    }
}

void priorityScheduling(struct Process proc[], int n) {
    struct Process temp;
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (proc[i].priority > proc[j].priority) {
                temp = proc[i];
                proc[i] = proc[j];
                proc[j] = temp;
            }
        }
    }

    calculateWaitingTime(proc, n);
    calculateTurnaroundTime(proc, n);

    
    printf("\nProcess\tPriority\tBurst Time\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t\t%d\t\t%d\t\t%d\n",
               proc[i].pid,
               proc[i].priority,
               proc[i].burstTime,
               proc[i].waitingTime,
               proc[i].turnaroundTime);
    }

    
    float totalWaiting = 0, totalTurnaround = 0;
    for (int i = 0; i < n; i++) {
        totalWaiting += proc[i].waitingTime;
        totalTurnaround += proc[i].turnaroundTime;
    }
    printf("\nAverage Waiting Time = %.2f\n", totalWaiting / n);
    printf("Average Turnaround Time = %.2f\n", totalTurnaround / n);
}

int main() {
    int n;
    printf("Enter number of processes: ");
    scanf("%d", &n);

    struct Process proc[n];

    for (int i = 0; i < n; i++) {
        proc[i].pid = i + 1;
        printf("Enter burst time for process %d: ", i + 1);
        scanf("%d", &proc[i].burstTime);
        printf("Enter priority for process %d (lower number = higher priority): ", i + 1);
        scanf("%d", &proc[i].priority);
    }

    priorityScheduling(proc, n);

    return 0;
}
