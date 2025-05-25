#include <stdio.h>

#define MAX 10

struct Process {
    int id;
    int burstTime;
    int remainingTime;
    int waitingTime;
    int turnaroundTime;
};

void roundRobin(struct Process proc[], int n, int quantum) {
    int time = 0;
    int completed = 0;

    while (completed < n) {
        for (int i = 0; i < n; i++) {
            if (proc[i].remainingTime > 0) {
                if (proc[i].remainingTime <= quantum) {
                    time += proc[i].remainingTime;
                    proc[i].waitingTime = time - proc[i].burstTime;
                    proc[i].remainingTime = 0;
                    completed++;
                } else {
                    time += quantum;
                    proc[i].remainingTime -= quantum;
                }
            }
        }
    }

    printf("\nProcess ID\tBurst Time\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++) {
        proc[i].turnaroundTime = proc[i].waitingTime + proc[i].burstTime;
        printf("%d\t\t%d\t\t%d\t\t%d\n", proc[i].id, proc[i].burstTime, proc[i].waitingTime, proc[i].turnaroundTime);
    }
}

int main() {
    int n, quantum;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    struct Process proc[MAX];

    for (int i = 0; i < n; i++) {
        proc[i].id = i + 1;
        printf("Enter burst time for process %d: ", i + 1);
        scanf("%d", &proc[i].burstTime);
        proc[i].remainingTime = proc[i].burstTime;
        proc[i].waitingTime = 0;
        proc[i].turnaroundTime = 0;
    }

    printf("Enter the time quantum: ");
    scanf("%d", &quantum);

    roundRobin(proc, n, quantum);

    return 0;
}
