#include <stdio.h>
#include <stdlib.h> 
#include "enemy.h"
#include "game.h"

// Funciones para Enemy
void initEnemy(NaveEnemiga *enemy)
{
    enemy->x = rand() % FIELD_WIDTH;
    enemy->y = 1;
    enemy->active = 1;
    enemy->type = BASIC_TYPE;
    enemy->size_in_mem = 1;
    enemy->update = updateEnemy;
    enemy->render = renderEnemy;
    enemy->fire = fireEnemyBullet;
    enemy->moveDown = moveEnemyDown;
    enemy->moveSide = NULL; // Por defecto, no se mueve lateralmente
}

void initMovingEnemy(NaveEnemiga *enemy)
{
    enemy->x = rand() % FIELD_WIDTH;
    enemy->y = 1;
    enemy->active = 1;
    enemy->type = MOVING_TYPE;
    enemy->size_in_mem = 2;
    enemy->update = updateEnemy; // Asegúrate de que apunte a la función correcta
    enemy->render = renderEnemy;
    enemy->fire = fireEnemyBullet;
    enemy->moveDown = moveEnemyDown;
    enemy->moveSide = moveEnemySide; // Habilitar el movimiento lateral
}

void initGeneralEnemy(NaveEnemiga *enemy)
{
    // EnemyType random_type = rand() % ENEMY_TYPE_COUNT;
    EnemyType random_type = 0;

    // Inicialización específica según el tipo
    switch (random_type)
    {
    case BASIC_TYPE:
        initEnemy(enemy);
        break;
    case MOVING_TYPE:
        initMovingEnemy(enemy);
        break;
        // Agrega más casos según los tipos de enemigos
    }
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
        if (rand() % 100 <= 30)
        {
            enemy->y++;
        }
    }
}

void moveEnemySide(NaveEnemiga *enemy)
{
    if (!enemy->active)
    {
        return;
    }

    if (rand() % 100 <= 30)
    {
        int direction = rand() % 3 - 1;
        enemy->x += direction;
        if (enemy->x <= 0 || enemy->x >= FIELD_WIDTH - 1)
        {
            direction = -direction;
        }
    }
}