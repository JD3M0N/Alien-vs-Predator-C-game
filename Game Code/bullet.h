#ifndef BULLET_H
#define BULLET_H

#include "ship.h" // Para declarar Ship

#define MAX_BULLETS 10

typedef struct
{
    int x;
    int y;
    int active;
} Bullet;

void initBullet(Bullet *bullet);
void fireBullet(Bullet *bullet, int x, int y); // Agregar x e y
void updateBullet(Bullet *bullet);
void renderBullet(Bullet *bullet);

#endif