#include <stdio.h>

#define MAX_BLOCKS 20
#define MAX_PROCESSES 20

void worstFit(int blockSize[], int m, int processSize[], int n) {
    int allocation[n];
    int tempBlock[m];

    for (int i = 0; i < m; i++)
        tempBlock[i] = blockSize[i];

    for (int i = 0; i < n; i++) {
        int wstIdx = -1;
        for (int j = 0; j < m; j++) {
            if (tempBlock[j] >= processSize[i]) {
                if (wstIdx == -1 || tempBlock[j] > tempBlock[wstIdx])
                    wstIdx = j;
            }
        }
        if (wstIdx != -1) {
            allocation[i] = wstIdx;
            tempBlock[wstIdx] -= processSize[i];
        } else
            allocation[i] = -1;
    }

    printf("\nWorst Fit Allocation:\nProcess No.\tProcess Size\tBlock No.\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t\t%d\t\t", i+1, processSize[i]);
        if (allocation[i] != -1)
            printf("%d\n", allocation[i]+1);
        else
            printf("Not Allocated\n");
    }
}

void bestFit(int blockSize[], int m, int processSize[], int n) {
    int allocation[n];
    int tempBlock[m];

    for (int i = 0; i < m; i++)
        tempBlock[i] = blockSize[i];

    for (int i = 0; i < n; i++) {
        int bestIdx = -1;
        for (int j = 0; j < m; j++) {
            if (tempBlock[j] >= processSize[i]) {
                if (bestIdx == -1 || tempBlock[j] < tempBlock[bestIdx])
                    bestIdx = j;
            }
        }
        if (bestIdx != -1) {
            allocation[i] = bestIdx;
            tempBlock[bestIdx] -= processSize[i];
        } else
            allocation[i] = -1;
    }

    printf("\nBest Fit Allocation:\nProcess No.\tProcess Size\tBlock No.\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t\t%d\t\t", i+1, processSize[i]);
        if (allocation[i] != -1)
            printf("%d\n", allocation[i]+1);
        else
            printf("Not Allocated\n");
    }
}

void firstFit(int blockSize[], int m, int processSize[], int n) {
    int allocation[n];
    int tempBlock[m];

    for (int i = 0; i < m; i++)
        tempBlock[i] = blockSize[i];

    for (int i = 0; i < n; i++) {
        allocation[i] = -1;
        for (int j = 0; j < m; j++) {
            if (tempBlock[j] >= processSize[i]) {
                allocation[i] = j;
                tempBlock[j] -= processSize[i];
                break;
            }
        }
    }

    printf("\nFirst Fit Allocation:\nProcess No.\tProcess Size\tBlock No.\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t\t%d\t\t", i+1, processSize[i]);
        if (allocation[i] != -1)
            printf("%d\n", allocation[i]+1);
        else
            printf("Not Allocated\n");
    }
}

int main() {
    int blockSize[MAX_BLOCKS], processSize[MAX_PROCESSES];
    int m, n;

    printf("Enter number of memory blocks: ");
    scanf("%d", &m);
    printf("Enter size of each block:\n");
    for (int i = 0; i < m; i++)
        scanf("%d", &blockSize[i]);

    printf("Enter number of processes: ");
    scanf("%d", &n);
    printf("Enter size of each process:\n");
    for (int i = 0; i < n; i++)
        scanf("%d", &processSize[i]);

    worstFit(blockSize, m, processSize, n);
    bestFit(blockSize, m, processSize, n);
    firstFit(blockSize, m, processSize, n);

    return 0;
}
