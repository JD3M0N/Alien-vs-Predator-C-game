#ifndef PROCESS_TABLE_H
#define PROCESS_TABLE_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/mman.h>
#include "game.h"  // Incluir game.h para que ENEMY_TOTAL_AMOUNT esté definido

#define MAX_PROCESSES (ENEMY_TOTAL_AMOUNT + 1)

typedef struct {
    pid_t pids[MAX_PROCESSES];
    int count;
    pthread_mutex_t mutex;
} ProcessTable;

extern ProcessTable *process_table;  // Cambiado a puntero para memoria compartida

void initProcessTable();
void addProcess(pid_t pid);
void printProcessTable();

#endif
