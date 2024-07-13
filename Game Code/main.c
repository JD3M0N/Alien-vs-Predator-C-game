#include <stdio.h>
#include <conio.h>   // Para _kbhit() y _getch()
#include <windows.h> // Para Sleep
#include "game.h"
#include "../processes/user_input_handler/input.h"

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
        Sleep(10); // Controla la velocidad del bucle
    }

    return 0;
}