#ifndef PROCESS_MANAGER_H
#define PROCESS_MANAGER_H

#include <sys/types.h>
#include <unistd.h>

#define MAX_PROCESSES 100
#define QUEUE_LEVELS 3

typedef struct {
    pid_t pid;
    char name[256];
    int priority;
    int queue_level;
} ProcessInfo;

typedef struct {
    ProcessInfo processes[MAX_PROCESSES];
    int count;
} ProcessQueue;

void initProcessManager();
void createEnemyProcesses(int num_enemies);
void createPlayerProcess();
void printProcessTable();
void scheduleProcesses();

#endif // PROCESS_MANAGER_H
