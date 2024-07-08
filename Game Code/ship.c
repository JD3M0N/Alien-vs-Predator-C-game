#include <stdio.h>
#include "ship.h"
#include "game.h"

void initShip(Ship *ship)
{
    ship->x = FIELD_WIDTH / 2;  // Posición inicial en el centro
    ship->y = FIELD_HEIGHT - 1; // Posición fija en la parte inferior
    ship->lives = 3; // Inicializa las vidas en 3
}

void updateShip(Ship *ship, char input)
{
    if (input == 'a' && ship->x > 1)
    { // Cambia 0 a 1 para no sobreponerse al borde
        ship->x--;
    }
    else if (input == 'd' && ship->x < FIELD_WIDTH - 2)
    { // Cambia FIELD_WIDTH-1 a FIELD_WIDTH-2
        ship->x++;
    }
}

void renderShip(Ship *ship)
{
    printf("\033[%d;%dH@", ship->y + 1, ship->x + 1); // Ajustar posición para bordes
}