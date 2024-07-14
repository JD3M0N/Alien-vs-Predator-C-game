#include "process_manager.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <signal.h>

ProcessQueue queues[QUEUE_LEVELS];
int current_level = 0;
int process_count = 0;

void initProcessManager() {
    for (int i = 0; i < QUEUE_LEVELS; i++) {
        queues[i].count = 0;
    }
    process_count = 0;
}

void addProcess(pid_t pid, const char* name, int priority, int queue_level) {
    if (process_count < MAX_PROCESSES) {
        ProcessInfo pInfo;
        pInfo.pid = pid;
        strncpy(pInfo.name, name, 255);
        pInfo.priority = priority;
        pInfo.queue_level = queue_level;
        queues[queue_level].processes[queues[queue_level].count++] = pInfo;
        process_count++;
    }
}

void createEnemyProcesses(int num_enemies) {
    for (int i = 0; i < num_enemies; i++) {
        pid_t pid = fork();
        if (pid == 0) {
            // Código del proceso enemigo
            execlp("./game", "game", "enemy", NULL); // Ejecutar el mismo ejecutable con argumento "enemy"
            perror("Error ejecutando el proceso enemigo");
            exit(1);
        } else if (pid > 0) {
            addProcess(pid, "Enemy", 1, 0);
        } else {
            perror("Error al crear el proceso enemigo");
        }
    }
}

void createPlayerProcess() {
    pid_t pid = fork();
    if (pid == 0) {
        // Código del proceso del jugador
        execlp("./game", "game", "player", NULL); // Ejecutar el mismo ejecutable con argumento "player"
        perror("Error ejecutando el proceso del jugador");
        exit(1);
    } else if (pid > 0) {
        addProcess(pid, "Player", 1, 0);
    } else {
        perror("Error al crear el proceso del jugador");
    }
}

void printProcessTable() {
    printf("PID\tName\tPriority\tQueue Level\n");
    for (int i = 0; i < QUEUE_LEVELS; i++) {
        for (int j = 0; j < queues[i].count; j++) {
            ProcessInfo pInfo = queues[i].processes[j];
            printf("%d\t%s\t%d\t\t%d\n", pInfo.pid, pInfo.name, pInfo.priority, pInfo.queue_level);
        }
    }
}

void moveProcessToLowerQueue(int pid) {
    for (int i = 0; i < QUEUE_LEVELS - 1; i++) {
        for (int j = 0; j < queues[i].count; j++) {
            if (queues[i].processes[j].pid == pid) {
                ProcessInfo pInfo = queues[i].processes[j];
                // Remove from current queue
                for (int k = j; k < queues[i].count - 1; k++) {
                    queues[i].processes[k] = queues[i].processes[k + 1];
                }
                queues[i].count--;
                // Add to lower queue
                pInfo.queue_level++;
                queues[i + 1].processes[queues[i + 1].count++] = pInfo;
                return;
            }
        }
    }
}

void scheduleProcesses() {
    static int current_process = 0;

    // Pause current running process if any
    for (int i = 0; i < QUEUE_LEVELS; i++) {
        if (current_process < queues[i].count) {
            kill(queues[i].processes[current_process].pid, SIGSTOP);
            break;
        }
    }

    // Find the next process to run
    for (int i = 0; i < QUEUE_LEVELS; i++) {
        if (queues[i].count > 0) {
            if (current_process >= queues[i].count) {
                current_process = 0;
            }
            ProcessInfo pInfo = queues[i].processes[current_process];
            kill(pInfo.pid, SIGCONT); // Continue the process
            sleep(1); // Simulate time slice
            current_process++;
            moveProcessToLowerQueue(pInfo.pid);
            break;
        }
    }
}
