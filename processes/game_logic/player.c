#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include "player.h"

void playerProcess() {
    pid_t parent_pid = getppid();
    while (1) {
        // Lógica del proceso del jugador
        printf("Proceso del jugador PID %d\n", getpid());
        kill(parent_pid, SIGUSR1); // Envía señal al proceso padre
        sleep(1);
    }
}
