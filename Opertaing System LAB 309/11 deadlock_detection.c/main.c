#include <stdio.h>

int main() {
    int n, m;
    printf("Enter number of processes: ");
    scanf("%d", &n);
    printf("Enter number of resources: ");
    scanf("%d", &m);

    int alloc[n][m], request[n][m], avail[m];
    int finish[n];

    printf("Enter allocation matrix:\n");
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            scanf("%d", &alloc[i][j]);

    printf("Enter request matrix:\n");
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            scanf("%d", &request[i][j]);

    printf("Enter available resources:\n");
    for (int i = 0; i < m; i++)
        scanf("%d", &avail[i]);

    for (int i = 0; i < n; i++) {
        int is_zero = 1;
        for (int j = 0; j < m; j++) {
            if (alloc[i][j] != 0) {
                is_zero = 0;
                break;
            }
        }
        finish[i] = is_zero;
    }

    int changed;
    do {
        changed = 0;
        for (int i = 0; i < n; i++) {
            if (finish[i] == 0) {
                int j;
                for (j = 0; j < m; j++) {
                    if (request[i][j] > avail[j])
                        break;
                }

                if (j == m) {
                    for (int k = 0; k < m; k++)
                        avail[k] += alloc[i][k];
                    finish[i] = 1;
                    changed = 1;
                }
            }
        }
    } while (changed);

    int deadlock = 0;
    for (int i = 0; i < n; i++) {
        if (finish[i] == 0) {
            deadlock = 1;
            printf("Process P%d is in deadlock.\n", i);
        }
    }

    if (!deadlock)
        printf("No deadlock detected.\n");

    return 0;
}
