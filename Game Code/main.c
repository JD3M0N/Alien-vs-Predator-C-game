#include <stdio.h>
#include <conio.h>   // Para _kbhit() y _getch()
#include <windows.h> // Para Sleep
#include "game.h"

int main()
{
    Game game;
    initGame(&game);

    while (1)
    {
        if (_kbhit())
        {
            char input = _getch();
            if (input == 'q')
            {
                break;
            }
            updateGame(&game, input);
        }
        renderGame(&game);
        Sleep(50); // Controla la velocidad del bucle
    }

    return 0;
}