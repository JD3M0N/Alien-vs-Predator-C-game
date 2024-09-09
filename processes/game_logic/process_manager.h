#ifndef PROCESS_MANAGER_H
#define PROCESS_MANAGER_H

#include <sys/types.h>
#include <unistd.h>
#include "../../Game Code/enemy.h"
// #include "../../Game Code/enemy.c"

#define MAX_PROCESSES 100
#define QUEUE_LEVELS 3
#define MAX_ENEMY_PROCESSES 20 // límite para el número de procesos enemigos

typedef struct {
    pid_t pid;
    int enemy_id; // ID de la nave enemiga
    int queue_level;
} ProcessInfo;

typedef struct {
    ProcessInfo processes[MAX_PROCESSES];
    int count;
} ProcessQueue;

void initProcessManager();
void createPlayerProcess();
void createEnemyProcess(NaveEnemiga* enemy, int pNaveEnemiga);
void removeProcess(int enemy_id);
void printProcessTable();
void scheduleProcesses();

#endif // PROCESS_MANAGER_H
