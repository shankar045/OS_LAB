#include <stdio.h>

int main() {
    int n;
    printf("Enter number of processes: ");
    scanf("%d", &n);

    int pid[n], at[n], bt[n], ct[n], tat[n], wt[n], completed[n];
    float total_tat = 0, total_wt = 0;

    printf("Enter arrival times:\n");
    for (int i = 0; i < n; i++) {
        pid[i] = i + 1;
        scanf("%d", &at[i]);
        completed[i] = 0;
    }

    printf("Enter burst times:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &bt[i]);
    }

    int time = 0, done = 0;
    while (done < n) {
        int min_bt = 9999, index = -1;
        for (int i = 0; i < n; i++) {
            if (at[i] <= time && completed[i] == 0 && bt[i] < min_bt) {
                min_bt = bt[i];
                index = i;
            }
        }

        if (index != -1) {
            time += bt[index];
            ct[index] = time;
            tat[index] = ct[index] - at[index];
            wt[index] = tat[index] - bt[index];
            completed[index] = 1;
            total_tat += tat[index];
            total_wt += wt[index];
            done++;
        } else {
            time++;
        }
    }

    printf("\nSJF Scheduling:\n");
    printf("PID\tAT\tBT\tCT\tTAT\tWT\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t%d\t%d\n", pid[i], at[i], bt[i], ct[i], tat[i], wt[i]);
    }

    printf("\nAverage Turnaround Time: %.2f ms", total_tat / n);
    printf("\nAverage Waiting Time: %.2f ms\n", total_wt / n);

    return 0;
}
