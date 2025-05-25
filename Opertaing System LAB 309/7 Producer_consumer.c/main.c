#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#define MAX 10

int *buffer, in = 0, out = 0, buffer_size;

HANDLE empty, full, mutex;

DWORD WINAPI producer(LPVOID param) {
    for (int i = 0; i < MAX; i++) {
        WaitForSingleObject(empty, INFINITE);
        WaitForSingleObject(mutex, INFINITE);

        buffer[in] = i + 1;
        printf("Produced: %d\n", buffer[in]);
        in = (in + 1) % buffer_size;

        ReleaseMutex(mutex);
        ReleaseSemaphore(full, 1, NULL);
        Sleep(1000);
    }
    return 0;
}

DWORD WINAPI consumer(LPVOID param) {
    for (int i = 0; i < MAX; i++) {
        WaitForSingleObject(full, INFINITE);
        WaitForSingleObject(mutex, INFINITE);

        printf("Consumed: %d\n", buffer[out]);
        out = (out + 1) % buffer_size;

        ReleaseMutex(mutex);
        ReleaseSemaphore(empty, 1, NULL);
        Sleep(2000);
    }
    return 0;
}

int main() {
    printf("Enter buffer size: ");
    scanf("%d", &buffer_size);

    buffer = (int*)malloc(buffer_size * sizeof(int));

    empty = CreateSemaphore(NULL, buffer_size, buffer_size, NULL);
    full = CreateSemaphore(NULL, 0, buffer_size, NULL);
    mutex = CreateMutex(NULL, FALSE, NULL);

    HANDLE hProducer, hConsumer;

    hProducer = CreateThread(NULL, 0, producer, NULL, 0, NULL);
    hConsumer = CreateThread(NULL, 0, consumer, NULL, 0, NULL);

    WaitForSingleObject(hProducer, INFINITE);
    WaitForSingleObject(hConsumer, INFINITE);

    CloseHandle(empty);
    CloseHandle(full);
    CloseHandle(mutex);
    free(buffer);

    return 0;
}
