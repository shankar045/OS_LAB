#include <stdio.h>
#include <windows.h>

#define N 5

HANDLE forks[N];
HANDLE threads[N];

DWORD WINAPI philosopher(LPVOID param) {
    int id = *(int*)param;
    int left = id;
    int right = (id + 1) % N;

    for (int i = 0; i < 3; i++) {
        printf("Philosopher %d is thinking\n", id);
        Sleep(1000);

        if (id == N - 1) {
            WaitForSingleObject(forks[right], INFINITE);
            WaitForSingleObject(forks[left], INFINITE);
        } else {
            WaitForSingleObject(forks[left], INFINITE);
            WaitForSingleObject(forks[right], INFINITE);
        }

        printf("Philosopher %d is eating\n", id);
        Sleep(2000);

        ReleaseMutex(forks[left]);
        ReleaseMutex(forks[right]);

        printf("Philosopher %d finished eating\n", id);
    }

    return 0;
}

int main() {
    int ids[N];

    for (int i = 0; i < N; i++) {
        forks[i] = CreateMutex(NULL, FALSE, NULL);
    }

    for (int i = 0; i < N; i++) {
        ids[i] = i;
        threads[i] = CreateThread(NULL, 0, philosopher, &ids[i], 0, NULL);
    }

    WaitForMultipleObjects(N, threads, TRUE, INFINITE);

    for (int i = 0; i < N; i++) {
        CloseHandle(forks[i]);
        CloseHandle(threads[i]);
    }

    return 0;
}
