#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <signal.h>
#include <string.h>
#include "game.h"
#include "../processes/user_input_handler/input.h"
#include "terminal_input.h"
#include "../processes/game_logic/process_manager.h"
#include "../processes/game_logic/enemy_logic.h"
#include "../processes/game_logic/player.h"

Game game;

void signalHandler(int signum) {
    if (signum == SIGUSR1) {
        if (_kbhit()) {
            user_input_handler();
            updateGame(&game, user_input_fr);
        }
        renderGame(&game);
    }
}

int main(int argc, char *argv[]) {
    if (argc > 1) {
        if (strcmp(argv[1], "enemy") == 0) {
            enemyProcess();
            return 0;
        } else if (strcmp(argv[1], "player") == 0) {
            playerProcess();
            return 0;
        }
    }

    srand(time(NULL)); // Inicializar rand con una semilla

    initProcessManager();
    //createEnemyProcesses(5);       // Crea procesos para enemigos
    createPlayerProcess();         // Crea el proceso para el jugador
    printProcessTable();           // Imprime la tabla de procesos

    signal(SIGUSR1, signalHandler); // Manejar la señal SIGUSR1

    initGame(&game);

    while (1) {
        scheduleProcesses();       // Ejecuta la planificación de procesos
        usleep(10000);             // Controla la velocidad del bucle (10 ms)
    }

    return 0;
}
