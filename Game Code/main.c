#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include "game.h"
#include "../processes/user_input_handler/input.h"
#include "terminal_input.h"

int main()
{
    srand(time(NULL)); // Inicializar rand con una semilla

    Game game;
    initGame(&game);

    while (1)
    {
        if (_kbhit())
        {
            user_input_handler();
            updateGame(&game, user_input_fr);
        }
        renderGame(&game);
        usleep(10000); // Controla la velocidad del bucle (10 ms)
    }

    return 0;
}
