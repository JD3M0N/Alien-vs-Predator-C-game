#include <stdio.h>
#include <stdlib.h> // Para system y malloc
#include "game.h"
#include "enemy.c"

// Función para verificar colisiones entre balas del jugador y del enemigo
void checkCollisions(Game *game)
{
    for (int i = 0; i < game->bullet_count; i++)
    {
        if (game->bullets[i].active)
        {
            for (int j = 0; j < MAX_ENEMY_BULLETS; j++)
            {
                if (game->enemy_bullets[j].active)
                {
                    if (game->bullets[i].x == game->enemy_bullets[j].x &&
                        game->bullets[i].y == game->enemy_bullets[j].y)
                    {
                        // Colisión detectada
                        game->bullets[i].active = 0;
                        game->enemy_bullets[j].active = 0;
                    }
                }
            }
        }
    }
}

void initGame(Game *game)
{
    initShip(&game->ship);
    game->bullets = NULL;
    game->bullet_count = 0;
    initEnemy(&game->enemy);
    for (int i = 0; i < MAX_ENEMY_BULLETS; i++)
    {
        initEnemyBullet(&game->enemy_bullets[i]);
    }
}

void updateGame(Game *game, char input)
{
    updateShip(&game->ship, input);
    if (input == ' ')
    {
        addBullet(game, game->ship.x, game->ship.y - 1); // Disparo un espacio por encima de la nave
    }
    for (int i = 0; i < game->bullet_count; i++)
    {
        updateBullet(&game->bullets[i]);
    }
    updateEnemy(&game->enemy);

    // Lógica para disparar la nave enemiga (por ejemplo, cada cierto tiempo)
    static int fire_counter = 0;
    if (fire_counter++ > 20)
    {
        fireEnemyBullet(game->enemy_bullets, &game->enemy);
        fire_counter = 0;
    }
    for (int i = 0; i < MAX_ENEMY_BULLETS; i++)
    {
        updateEnemyBullet(&game->enemy_bullets[i]);
    }

    // Verificar colisiones
    checkCollisions(game);
}

void renderGame(Game *game)
{
    system("cls"); // Limpia la pantalla en Windows

    // Dibuja los bordes del campo
    for (int i = 0; i <= FIELD_WIDTH + 1; i++)
    {
        printf("#");
    }
    printf("\n");
    for (int i = 0; i < FIELD_HEIGHT; i++)
    {
        printf("#");
        for (int j = 0; j < FIELD_WIDTH; j++)
        {
            printf(" ");
        }
        printf("#\n");
    }
    for (int i = 0; i <= FIELD_WIDTH + 1; i++)
    {
        printf("#");
    }
    printf("\n");

    // Dibuja la nave y los disparos del jugador
    renderShip(&game->ship);
    for (int i = 0; i < game->bullet_count; i++)
    {
        renderBullet(&game->bullets[i]);
    }

    // Dibuja la nave enemiga y sus disparos
    renderEnemy(&game->enemy);
    for (int i = 0; i < MAX_ENEMY_BULLETS; i++)
    {
        renderEnemyBullet(&game->enemy_bullets[i]);
    }
}

void addBullet(Game *game, int x, int y)
{
    game->bullets = realloc(game->bullets, (game->bullet_count + 1) * sizeof(Bullet));
    initBullet(&game->bullets[game->bullet_count]);
    game->bullets[game->bullet_count].x = x;
    game->bullets[game->bullet_count].y = y;
    game->bullets[game->bullet_count].active = 1;
    game->bullet_count++;
}