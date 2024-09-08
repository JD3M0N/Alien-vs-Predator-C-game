#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include "enemy_logic.h"

void enemyProcess() {
    pid_t parent_pid = getppid();
    while (1) {
        // Lógica del proceso enemigo
        printf("Proceso enemigo PID %d\n", getpid());
        kill(parent_pid, SIGUSR1); // Envía señal al proceso padre
        sleep(1);
    }
}
