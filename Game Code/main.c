#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <sys/wait.h>
#include "game.h"
#include "../processes/user_input_handler/input.h"
#include "terminal_input.h"
#include "../processes/user_input_handler/global_signals.h"
#include "process_table.h"
#include "process_scheduling.h"

void create_process_for_ship(Game *game, int ship_index, int is_player) {
    pid_t pid = fork();
    if (pid == 0) {
        // Código del proceso hijo
        if (is_player) {
            while (1) {
                if (_kbhit()) {
                    user_input_handler();
                    updateGame(game, user_input_fr);
                }
                renderGame(game);
                usleep(10000); // Controla la velocidad del bucle (10 ms)
            }
        } else {
            NaveEnemiga *enemy = &game->enemies[ship_index];
            while (enemy->active) {
                updateEnemy(enemy);
                renderEnemy(enemy);
                usleep(100000); // Controla la velocidad del bucle para enemigos
            }
        }
        exit(0);
    } else {
        // Guardar PID en la tabla de procesos
        addProcess(pid);
        if (is_player) {
            game->player_pid = pid;
        } else {
            game->enemy_pids[ship_index] = pid;
        }
        printf("Created process for %s, PID = %d\n", is_player ? "player" : "enemy", pid); // Depuración
    }
}

int main() {
    srand(time(NULL)); // Inicializar rand con una semilla

    Game game;
    initGame(&game);
    initProcessTable();  // Inicializar la tabla de procesos compartida
    initMLFQ();

    // Crear proceso para la nave del jugador
    create_process_for_ship(&game, -1, 1);

    // Crear procesos para las naves enemigas
    for (int i = 0; i < ENEMY_TOTAL_AMOUNT; i++) {
        create_process_for_ship(&game, i, 0);
    }

    // Añadir procesos a las colas de MLFQ
    addProcessToQueue(game.player_pid, 0);
    for (int i = 0; i < ENEMY_TOTAL_AMOUNT; i++) {
        addProcessToQueue(game.enemy_pids[i], 1);
    }

    // Ejecutar los procesos
    executeProcesses();

    // Esperar a que todos los procesos hijos terminen
    int status;
    for (int i = 0; i < ENEMY_TOTAL_AMOUNT + 1; i++) {
        wait(&status);
    }

    return 0;
}
