#include <stdio.h>
#include "bullet.h"

void initBullet(Bullet *bullet)
{
    bullet->x = -1; // Posición inicial fuera de la pantalla
    bullet->y = -1;
    bullet->active = 0;
}

void updateBullet(Bullet *bullet)
{
    if (bullet->active)
    {
        bullet->y--;
        if (bullet->y < 0)
        {
            bullet->active = 0;
        }
    }
}

void renderBullet(Bullet *bullet)
{
    if (bullet->active)
    {
        printf("\033[%d;%dH|", bullet->y + 1, bullet->x + 1); // Ajustar para bordes
    }
}
