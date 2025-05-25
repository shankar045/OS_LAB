#include <stdio.h>

int main() {
    int n;
    printf("Enter number of processes: ");
    scanf("%d", &n);

    int pid[n], bt[n], ct[n], tat[n], wt[n], type[n];
    int sys_index = 0, user_index = 0;
    int sys_bt[n], sys_pid[n];
    int user_bt[n], user_pid[n];

    for (int i = 0; i < n; i++) {
        pid[i] = i + 1;
        printf("Enter type for process %d (0-System, 1-User): ", i + 1);
        scanf("%d", &type[i]);
        printf("Enter burst time for process %d: ", i + 1);
        scanf("%d", &bt[i]);

        if (type[i] == 0) {
            sys_pid[sys_index] = pid[i];
            sys_bt[sys_index] = bt[i];
            sys_index++;
        } else {
            user_pid[user_index] = pid[i];
            user_bt[user_index] = bt[i];
            user_index++;
        }
    }

    int time = 0;
    printf("\nMulti-Level Queue Scheduling:\n");
    printf("PID\tType\tBT\tCT\tTAT\tWT\n");

    for (int i = 0; i < sys_index; i++) {
        time += sys_bt[i];
        ct[i] = time;
        tat[i] = ct[i];
        wt[i] = tat[i] - sys_bt[i];
        printf("%d\tSystem\t%d\t%d\t%d\t%d\n", sys_pid[i], sys_bt[i], ct[i], tat[i], wt[i]);
    }

    for (int i = 0; i < user_index; i++) {
        time += user_bt[i];
        ct[sys_index + i] = time;
        tat[sys_index + i] = ct[sys_index + i];
        wt[sys_index + i] = tat[sys_index + i] - user_bt[i];
        printf("%d\tUser\t%d\t%d\t%d\t%d\n", user_pid[i], user_bt[i], ct[sys_index + i], tat[sys_index + i], wt[sys_index + i]);
    }

    return 0;
}
