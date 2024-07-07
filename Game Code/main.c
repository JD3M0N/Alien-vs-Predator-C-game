#include <stdio.h>
#include <conio.h>   // Para _kbhit() y _getch()
#include <windows.h> // Para Sleep
#include "game.h"
#include "../processes/user_input_handler/input.h"

int main()
{
    Game game;
    initGame(&game);

    while (1)
    {
        if (_kbhit())
        {
            // char input = _getch();
            // if (input == 'q')
            // {
            //     break;
            // }

            user_input_handler();

            // // --------------- Esto va en otro archivo.c o .h --------------------------------
            // pthread_mutex_lock(&user_ship);
            // while (1)
            //     pthread_cond_wait(&can_change_ship, &user_ship);

            // index--;
            updateGame(&game, user_input_fr);

            // pthread_cond_signal(&can_read);
            // pthread_mutex_unlock(&user_ship);

            // --------------- Esto va en otro archivo.c o .h --------------------------------
        }
        renderGame(&game);
        Sleep(10); // Controla la velocidad del bucle
    }

    return 0;
}