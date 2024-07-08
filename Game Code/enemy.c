#include <stdio.h>
#include "enemy.h"
#include "game.h"

// Funciones para Enemy
void initEnemy(Enemy *enemy)
{
    enemy->base.x = FIELD_WIDTH / 2;
    enemy->base.y = 1;
    enemy->base.active = 1;
    enemy->base.update = updateEnemy;
    enemy->base.render = renderEnemy;
    enemy->base.fire = fireEnemyBullet;
}

void updateEnemy(NaveEnemiga *enemy)
{
    // Implementar lógica de actualización para Enemy
}

void renderEnemy(NaveEnemiga *enemy)
{
    if (enemy->active)
    {
        printf("\033[%d;%dH^", enemy->y + 1, enemy->x + 1);
    }
}

void initEnemyBullet(EnemyBullet *bullet)
{
    bullet->x = -1; // Posición inicial fuera de la pantalla
    bullet->y = -1;
    bullet->active = 0;
}

void fireEnemyBullet(NaveEnemiga *enemy, EnemyBullet bullets[])
{
    if (!enemy->active)
    {
        return; // No disparar si el enemigo no está activo
    }
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

// Funciones para MovingEnemy
void initMovingEnemy(MovingEnemy *enemy)
{
    enemy->base.x = FIELD_WIDTH / 2;
    enemy->base.y = 2;
    enemy->base.active = 1;
    enemy->base.update = updateMovingEnemy;
    enemy->base.render = renderMovingEnemy;
    enemy->base.fire = fireMovingEnemyBullet;
    enemy->direction = 1;
}

void updateMovingEnemy(NaveEnemiga *enemy)
{
    MovingEnemy *moving_enemy = (MovingEnemy *)enemy; // Convertir a MovingEnemy
    if (moving_enemy->base.active)
    {
        moving_enemy->base.x += moving_enemy->direction;
        if (moving_enemy->base.x <= 0 || moving_enemy->base.x >= FIELD_WIDTH - 1)
        {
            moving_enemy->direction *= -1;
        }
    }
}

void renderMovingEnemy(NaveEnemiga *enemy)
{
    if (enemy->active)
    {
        printf("\033[%d;%dH^", enemy->y + 1, enemy->x + 1);
    }
}

void fireMovingEnemyBullet(NaveEnemiga *enemy, EnemyBullet bullets[])
{
    if (!enemy->active)
    {
        return; // No disparar si el enemigo no está activo
    }
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
