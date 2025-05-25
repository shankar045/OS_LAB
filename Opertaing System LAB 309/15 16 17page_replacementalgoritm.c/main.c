#include <stdio.h>
#include <stdbool.h>

#define MAX 100

// Function to check if page is in frame
bool isInFrame(int frames[], int n, int page) {
    for (int i = 0; i < n; i++)
        if (frames[i] == page)
            return true;
    return false;
}

// FIFO Page Replacement
void fifo(int pages[], int n, int framesCount) {
    int frames[framesCount];
    int pageFaults = 0, index = 0;

    for (int i = 0; i < framesCount; i++)
        frames[i] = -1;

    printf("\nFIFO Page Replacement:\n");
    for (int i = 0; i < n; i++) {
        if (!isInFrame(frames, framesCount, pages[i])) {
            frames[index] = pages[i];
            index = (index + 1) % framesCount;
            pageFaults++;
        }

        // Print current frame status
        printf("Page %d: ", pages[i]);
        for (int j = 0; j < framesCount; j++)
            if (frames[j] != -1)
                printf("%d ", frames[j]);
        printf("\n");
    }

    printf("Total Page Faults (FIFO): %d\n", pageFaults);
}

// Find LRU index
int findLRU(int time[], int n) {
    int min = time[0], pos = 0;
    for (int i = 1; i < n; ++i) {
        if (time[i] < min) {
            min = time[i];
            pos = i;
        }
    }
    return pos;
}

// LRU Page Replacement
void lru(int pages[], int n, int framesCount) {
    int frames[framesCount], time[framesCount];
    int pageFaults = 0, counter = 0;

    for (int i = 0; i < framesCount; i++) {
        frames[i] = -1;
        time[i] = 0;
    }

    printf("\nLRU Page Replacement:\n");
    for (int i = 0; i < n; i++) {
        int flag1 = 0, flag2 = 0;

        for (int j = 0; j < framesCount; j++) {
            if (frames[j] == pages[i]) {
                counter++;
                time[j] = counter;
                flag1 = flag2 = 1;
                break;
            }
        }

        if (!flag1) {
            for (int j = 0; j < framesCount; j++) {
                if (frames[j] == -1) {
                    counter++;
                    pageFaults++;
                    frames[j] = pages[i];
                    time[j] = counter;
                    flag2 = 1;
                    break;
                }
            }
        }

        if (!flag2) {
            int pos = findLRU(time, framesCount);
            counter++;
            pageFaults++;
            frames[pos] = pages[i];
            time[pos] = counter;
        }

        printf("Page %d: ", pages[i]);
        for (int j = 0; j < framesCount; j++)
            if (frames[j] != -1)
                printf("%d ", frames[j]);
        printf("\n");
    }

    printf("Total Page Faults (LRU): %d\n", pageFaults);
}

// Optimal Page Replacement
void optimal(int pages[], int n, int framesCount) {
    int frames[framesCount];
    int pageFaults = 0;

    for (int i = 0; i < framesCount; i++)
        frames[i] = -1;

    printf("\nOptimal Page Replacement:\n");
    for (int i = 0; i < n; i++) {
        if (!isInFrame(frames, framesCount, pages[i])) {
            int replaceIndex = -1;
            int farthest = i + 1;

            for (int j = 0; j < framesCount; j++) {
                int k;
                for (k = i + 1; k < n; k++) {
                    if (frames[j] == pages[k]) break;
                }

                if (k == n) {
                    replaceIndex = j;
                    break;
                }

                if (k > farthest) {
                    farthest = k;
                    replaceIndex = j;
                }

                if (replaceIndex == -1)
                    replaceIndex = 0;
            }

            frames[replaceIndex] = pages[i];
            pageFaults++;
        }

        printf("Page %d: ", pages[i]);
        for (int j = 0; j < framesCount; j++)
            if (frames[j] != -1)
                printf("%d ", frames[j]);
        printf("\n");
    }

    printf("Total Page Faults (Optimal): %d\n", pageFaults);
}

int main() {
    int pages[MAX], n, frames;

    printf("Enter number of pages: ");
    scanf("%d", &n);

    printf("Enter page reference string:\n");
    for (int i = 0; i < n; i++)
        scanf("%d", &pages[i]);

    printf("Enter number of frames: ");
    scanf("%d", &frames);

    fifo(pages, n, frames);
    lru(pages, n, frames);
    optimal(pages, n, frames);

    return 0;
}
