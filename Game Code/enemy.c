#include <stdio.h>
#include "enemy.h"
#include "game.h"

// Funciones para Enemy
void initEnemy(NaveEnemiga *enemy)
{
    enemy->x = 5;
    enemy->y = 1;
    enemy->active = 1;
    enemy->direction = NULL;
    enemy->update = updateEnemy;
    enemy->render = renderEnemy;
    enemy->fire = fireEnemyBullet;
    enemy->moveDown = moveEnemyDown;
    enemy->moveSide = NULL; // Por defecto, no se mueve lateralmente
}

void initMovingEnemy(NaveEnemiga *enemy)
{
    enemy->x = 15;
    enemy->y = 1;
    enemy->active = 1;
    enemy->direction = 1;        // Inicializa la dirección
    enemy->update = updateEnemy; // Asegúrate de que apunte a la función correcta
    enemy->render = renderEnemy;
    enemy->fire = fireEnemyBullet;
    enemy->moveDown = moveEnemyDown;
    enemy->moveSide = moveEnemySide; // Habilitar el movimiento lateral
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

void moveEnemyDown(NaveEnemiga *enemy)
{
    if (enemy->active)
    {
        enemy->y++;
    }
}

void moveEnemySide(NaveEnemiga *enemy)
{
    if (!enemy->active)
    {
        return;
    }

    static int direction = 1;
    enemy->x += direction;
    if (enemy->x <= 0 || enemy->x >= FIELD_WIDTH - 1)
    {
        direction = -direction;
        enemy->y++; // Baja un nivel al cambiar de dirección
    }
}