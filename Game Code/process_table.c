#include "process_table.h"

ProcessTable *process_table;

void initProcessTable() {
    process_table = mmap(NULL, sizeof(ProcessTable), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    if (process_table == MAP_FAILED) {
        perror("mmap");
        exit(EXIT_FAILURE);
    }

    process_table->count = 0;
    pthread_mutexattr_t attr;
    pthread_mutexattr_init(&attr);
    pthread_mutexattr_setpshared(&attr, PTHREAD_PROCESS_SHARED);
    pthread_mutex_init(&process_table->mutex, &attr);
    printf("Initialized process table\n"); // Depuración
}

void addProcess(pid_t pid) {
    pthread_mutex_lock(&process_table->mutex);
    if (process_table->count < MAX_PROCESSES) {
        process_table->pids[process_table->count++] = pid;
        printf("Added process PID = %d, count = %d\n", pid, process_table->count); // Depuración
    }
    pthread_mutex_unlock(&process_table->mutex);
}

void printProcessTable() {
    pthread_mutex_lock(&process_table->mutex);
    printf("Process Table:\n");
    for (int i = 0; i < process_table->count; i++) {
        printf("Process %d: PID = %d\n", i, process_table->pids[i]);
    }
    pthread_mutex_unlock(&process_table->mutex);
}
