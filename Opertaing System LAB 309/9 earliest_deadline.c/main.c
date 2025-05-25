#include <stdio.h>
#include <stdlib.h>

#define MAX 10

typedef struct {
    int id, arr, exe, dl, rem;
} Task;

int cmp(const void *a, const void *b) {
    return ((Task*)a)->dl - ((Task*)b)->dl;
}

void schedule(Task t[], int n) {
    qsort(t, n, sizeof(Task), cmp);
    for (int time = 0, completed = 0; completed < n; time++) {
        Task *next = NULL;
        for (int i = 0; i < n; i++)
            if (t[i].arr <= time && t[i].rem > 0)
                if (!next || t[i].dl < next->dl)
                    next = &t[i];

        if (next) {
            printf("Time %d: Task %d starts\n", time, next->id);
            time += next->exe - 1;
            next->rem = 0;
            printf("Time %d: Task %d done\n", time + 1, next->id);
            completed++;
        }
    }
}

int main() {
    int n;
    Task t[MAX];
    printf("Enter task count: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        t[i].id = i + 1;
        printf("Enter arrival, execution, deadline for task %d: ", i + 1);
        scanf("%d%d%d", &t[i].arr, &t[i].exe, &t[i].dl);
        t[i].rem = t[i].exe;
    }

    schedule(t, n);
    return 0;
}
