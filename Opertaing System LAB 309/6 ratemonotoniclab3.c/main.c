#include <stdio.h>

int main() {
    int n, time = 0, i, j;
    printf("Enter number of processes: ");
    scanf("%d", &n);

    int pid[n], bt[n], period[n], next_deadline[n], remaining_bt[n];

    for (i = 0; i < n; i++) {
        pid[i] = i + 1;
        printf("Enter burst time for process %d: ", pid[i]);
        scanf("%d", &bt[i]);
        printf("Enter period for process %d: ", pid[i]);
        scanf("%d", &period[i]);
        remaining_bt[i] = bt[i];
        next_deadline[i] = period[i];
    }

    int total_time;
    printf("Enter total time to schedule: ");
    scanf("%d", &total_time);

    printf("\nRate Monotonic Scheduling:\n");

    for (time = 0; time < total_time; time++) {
        int min_period = 9999, selected = -1;

        for (i = 0; i < n; i++) {
            if (remaining_bt[i] > 0 && period[i] < min_period && time < next_deadline[i]) {
                min_period = period[i];
                selected = i;
            }
        }

        if (selected != -1) {
            printf("Time %d: Process %d running\n", time, pid[selected]);
            remaining_bt[selected]--;

            if (remaining_bt[selected] == 0) {
                remaining_bt[selected] = bt[selected];
                next_deadline[selected] += period[selected];
            }
        } else {
            printf("Time %d: CPU Idle\n", time);
        }

        for (j = 0; j < n; j++) {
            if (time + 1 == next_deadline[j] && remaining_bt[j] > 0) {
                printf("Time %d: Process %d missed deadline\n", time + 1, pid[j]);
                remaining_bt[j] = bt[j];
                next_deadline[j] += period[j];
            }
        }
    }

    return 0;
}
