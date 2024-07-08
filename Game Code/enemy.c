#include <stdio.h>
#include "enemy.h"
#include "game.h"

void initEnemy(Enemy *enemy)
{
    enemy->x = FIELD_WIDTH / 2;
    enemy->y = 1; // Posición inicial en la parte superior del campo
}

void updateEnemy(Enemy *enemy)
{
    // Lógica de movimiento de la nave enemiga (por ahora, estática)
}

void renderEnemy(Enemy *enemy)
{
    printf("\033[%d;%dH^", enemy->y + 1, enemy->x + 1);
}

void initEnemyBullet(EnemyBullet *bullet)
{
    bullet->x = -1; // Posición inicial fuera de la pantalla
    bullet->y = -1;
    bullet->active = 0;
}

void fireEnemyBullet(EnemyBullet bullets[], Enemy *enemy)
{
    for (int i = 0; i < MAX_ENEMY_BULLETS; i++)
    {
        if (!bullets[i].active)
        {
            bullets[i].x = enemy->x;
            bullets[i].y = enemy->y + 1;
            bullets[i].active = 1;
            break;
        }
    }
}

void updateEnemyBullet(EnemyBullet *bullet)
{
    if (bullet->active)
    {
        bullet->y++;
        if (bullet->y >= FIELD_HEIGHT)
        {
            bullet->active = 0;
        }
    }
}

void renderEnemyBullet(EnemyBullet *bullet)
{
    if (bullet->active)
    {
        printf("\033[%d;%dH|", bullet->y + 1, bullet->x + 1);
    }
}

void initMovingEnemy(MovingEnemy *enemy)
{
    enemy->x = FIELD_WIDTH / 2;
    enemy->y = 2; // Posición inicial más abajo que el primer enemigo
    enemy->active = 1;
    enemy->direction = 1; // Empieza moviéndose a la derecha
}

void updateMovingEnemy(MovingEnemy *enemy)
{
    if (enemy->active)
    {
        enemy->x += enemy->direction;
        if (enemy->x <= 0 || enemy->x >= FIELD_WIDTH - 1)
        {
            enemy->direction *= -1; // Cambia de dirección al llegar a los bordes
        }
    }
}

void renderMovingEnemy(MovingEnemy *enemy)
{
    if (enemy->active)
    {
        printf("\033[%d;%dH^", enemy->y + 1, enemy->x + 1);
    }
}

void fireMovingEnemyBullet(EnemyBullet bullets[], MovingEnemy *enemy)
{
    for (int i = 0; i < MAX_ENEMY_BULLETS; i++)
    {
        if (!bullets[i].active)
        {
            bullets[i].x = enemy->x;
            bullets[i].y = enemy->y + 1;
            bullets[i].active = 1;
            break;
        }
    }
}
