#ifndef GAME_H
#define GAME_H

#include "ship.h"
#include "bullet.h"
#include "enemy.h"

#define FIELD_WIDTH 40
#define FIELD_HEIGHT 20

typedef struct
{
    Ship ship;
    Bullet *bullets;
    int bullet_count;
    NaveEnemiga *enemies[2]; // Array de punteros a NaveEnemiga
    EnemyBullet enemy_bullets[MAX_ENEMY_BULLETS];
} Game;

void initGame(Game *game);
void updateGame(Game *game, char input);
void renderGame(Game *game);
void addBullet(Game *game, int x, int y);

#endif