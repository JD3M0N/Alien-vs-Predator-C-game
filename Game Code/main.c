#include <stdio.h>
#include <stdlib.h>  // Para rand()
#include <unistd.h>  // Para usleep()
#include <termios.h> // Para configuración de terminal
#include <fcntl.h>   // Para configuración de terminal
#include <time.h>    // Para srand()

#include "game.h"
#include "../processes/user_input_handler/input.h"

int _kbhit(void)
{
    struct termios oldt, newt;
    int ch;
    int oldf;

    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);

    ch = getchar();

    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    fcntl(STDIN_FILENO, F_SETFL, oldf);

    if (ch != EOF)
    {
        ungetc(ch, stdin);
        return 1;
    }

    return 0;
}

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
