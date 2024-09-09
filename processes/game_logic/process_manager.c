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
ProcessInfo enemy_processes[MAX_ENEMY_PROCESSES]; // Almacena procesos de enemigos
int enemy_process_count = 0; // Cuenta procesos de enemigos

void initProcessManager() {
    for (int i = 0; i < QUEUE_LEVELS; i++) {
        queues[i].count = 0;
    }
    process_count = 0;
    enemy_process_count = 0;
}

void addProcess(pid_t pid, int enemy_id, int queue_level) {
    if (process_count < MAX_PROCESSES) {
        ProcessInfo pInfo;
        pInfo.pid = pid;
        pInfo.enemy_id = enemy_id;
        pInfo.queue_level = queue_level;
        queues[queue_level].processes[queues[queue_level].count++] = pInfo;
        process_count++;
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
        int pPlatyer = 0;
        addProcess(pid, pPlatyer, 0);
    } else {
        perror("Error al crear el proceso del jugador");
    }
}

void createEnemyProcess(NaveEnemiga* enemy, int pNaveEnemiga) {
    pid_t pid = fork();
    if (pid == 0) {
        // Código del proceso enemigo
        execlp("./game", "game", "enemy", NULL); // Ejecutar el mismo ejecutable con argumento "enemy"
        perror("Error ejecutando el proceso enemigo");
        exit(1);
    } else if (pid > 0) {
        // Asociar el proceso con la nave enemiga
        addProcess(pid, pNaveEnemiga, 0);
        enemy_processes[enemy_process_count].pid = pid;
        enemy_processes[enemy_process_count].enemy_id = pNaveEnemiga;
        enemy_process_count++;
    } else {
        perror("Error al crear el proceso enemigo");
    }
}

void removeProcess(int enemy_id) {
    for (int i = 0; i < enemy_process_count; i++) {
        if (enemy_processes[i].enemy_id == enemy_id) {
            kill(enemy_processes[i].pid, SIGKILL); // Termina el proceso
            waitpid(enemy_processes[i].pid, NULL, 0); // Espera a que termine el proceso
            // Reorganizar la lista de procesos
            for (int j = i; j < enemy_process_count - 1; j++) {
                enemy_processes[j] = enemy_processes[j + 1];
            }
            enemy_process_count--;
            break;
        }
    }
}

void printProcessTable() {
    printf("PID\tName\tPriority\tQueue Level\n");
    for (int i = 0; i < QUEUE_LEVELS; i++) {
        for (int j = 0; j < queues[i].count; j++) {
            ProcessInfo pInfo = queues[i].processes[j];
            printf("%d\t%s\t%d\t\t%d\n", pInfo.pid, "Enemy", 1, pInfo.queue_level);
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
            break;
        }
    }
}
