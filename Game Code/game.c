#include <stdio.h>
#include <stdlib.h> // Para system y malloc
#include "game.h"
#include "enemy.h"

void checkCollisions(Game *game)
{
    // Verificar colisiones entre balas del jugador y enemigos
    for (int i = 0; i < game->bullet_count; i++)
    {
        Bullet *bullet = &game->bullets[i];
        if (bullet->active)
        {
            for (int j = 0; j < 2; j++)
            {
                NaveEnemiga *enemy = game->enemies[j];
                if (enemy->active && bullet->x == enemy->x && bullet->y == enemy->y)
                {
                    bullet->active = 0;
                    enemy->active = 0;
                    // Desactivar las balas del enemigo si el enemigo es destruido
                    for (int k = 0; k < MAX_ENEMY_BULLETS; k++)
                    {
                        if (game->enemy_bullets[k].x == enemy->x && game->enemy_bullets[k].y >= enemy->y)
                        {
                            game->enemy_bullets[k].active = 0;
                        }
                    }
                }
            }
        }
    }

    // Verificar colisiones entre balas enemigas y la nave del jugador
    for (int i = 0; i < MAX_ENEMY_BULLETS; i++)
    {
        EnemyBullet *bullet = &game->enemy_bullets[i];
        if (bullet->active && bullet->x == game->ship.x && bullet->y == game->ship.y)
        {
            bullet->active = 0;
            game->ship.lives--;
            if (game->ship.lives <= 0)
            {
                game->game_over = 1; // Termina el juego si las vidas llegan a cero
            }
        }
    }

    // Verificar colisiones entre balas
    for (int i = 0; i < game->bullet_count; i++)
    {
        if (game->bullets[i].active)
        {
            for (int j = 0; j < MAX_ENEMY_BULLETS; j++)
            {
                if (game->enemy_bullets[j].active)
                {
                    // Verificar colisión en la misma posición
                    if (game->bullets[i].x == game->enemy_bullets[j].x &&
                        game->bullets[i].y == game->enemy_bullets[j].y)
                    {
                        game->bullets[i].active = 0;
                        game->enemy_bullets[j].active = 0;
                        printf("\033[%d;%dH*", game->bullets[i].y + 1, game->bullets[i].x + 1); // Mostrar colisión
                    }
                    // Verificar colisión cruzada inminente
                    else if (game->bullets[i].x == game->enemy_bullets[j].x &&
                             game->bullets[i].y == game->enemy_bullets[j].y + 1)
                    {
                        game->bullets[i].active = 0;
                        game->enemy_bullets[j].active = 0;
                        printf("\033[%d;%dH*", game->bullets[i].y + 1, game->bullets[i].x + 1);             // Mostrar colisión
                        printf("\033[%d;%dH*", game->enemy_bullets[j].y + 2, game->enemy_bullets[j].x + 1); // Mostrar colisión
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

    // Inicializar enemigos
    static Enemy enemy;
    static MovingEnemy moving_enemy;
    initEnemy(&enemy);
    initMovingEnemy(&moving_enemy);

    game->enemies[0] = (NaveEnemiga *)&enemy;
    game->enemies[1] = (NaveEnemiga *)&moving_enemy;

    for (int i = 0; i < MAX_ENEMY_BULLETS; i++)
    {
        initEnemyBullet(&game->enemy_bullets[i]);
    }

    game->game_over = 0; // Inicializa el juego como no terminado
}

void updateGame(Game *game, char input)
{
    if (game->game_over)
    {
        return; // No actualizar si el juego ha terminado
    }

    // Actualizar la nave del jugador
    updateShip(&game->ship, input);
    if (input == ' ')
    {
        addBullet(game, game->ship.x, game->ship.y - 1);
    }

    // Actualizar balas del jugador
    for (int i = 0; i < game->bullet_count; i++)
    {
        updateBullet(&game->bullets[i]);
    }

    // Actualizar enemigos
    for (int i = 0; i < 2; i++)
    {
        if (game->enemies[i]->active)
        {
            game->enemies[i]->update(game->enemies[i]); // Actualiza el enemigo
            /*

            game->enemies[i]->moveDown(game->enemies[i]); // Mover enemigos hacia abajo
            if (game->enemies[i]->moveSide)
            {
                game->enemies[i]->moveSide(game->enemies[i]); // Mover lateralmente si está habilitado
            }

            */
            // Verificar si el enemigo ha llegado a la tierra
            if (game->enemies[i]->y >= FIELD_HEIGHT - 1)
            {
                game->enemies[i]->active = 0;
                game->ship.lives--;
                if (game->ship.lives <= 0)
                {
                    game->game_over = 1; // Termina el juego si las vidas llegan a cero
                }
            }
        }
    }

    // Lógica para disparar la nave enemiga (por ejemplo, cada cierto tiempo)
    static int fire_counter = 0;
    if (fire_counter++ > 8)
    {
        for (int i = 0; i < 2; i++)
        {
            if (game->enemies[i]->active)
            {
                game->enemies[i]->fire(game->enemies[i], game->enemy_bullets);
            }
        }
        fire_counter = 0;
    }

    // Actualizar balas enemigas
    for (int i = 0; i < MAX_ENEMY_BULLETS; i++)
    {
        updateEnemyBullet(&game->enemy_bullets[i]);
    }

    // Verificar colisiones
    checkCollisions(game);
}

void renderGame(Game *game)
{
    system("cls");

    // Dibuja los bordes del campo con letras del alfabeto
    for (int i = 0; i <= FIELD_WIDTH + 1; i++)
    {
        printf("%c", ALPHABET_UPPER[i % 26]);
    }
    printf("\n");
    for (int i = 0; i < FIELD_HEIGHT; i++)
    {
        printf("%c", ALPHABET_UPPER[i % 26]);
        for (int j = 0; j < FIELD_WIDTH; j++)
        {
            printf(" ");
        }
        printf("%c\n", ALPHABET_UPPER[i % 26]);
    }
    for (int i = 0; i <= FIELD_WIDTH + 1; i++)
    {
        printf("%c", ALPHABET_UPPER[i % 26]);
    }
    printf("\n");

    // Dibuja la nave y los disparos del jugador
    renderShip(&game->ship);
    for (int i = 0; i < game->bullet_count; i++)
    {
        renderBullet(&game->bullets[i]);
    }

    // Dibuja los enemigos
    for (int i = 0; i < 2; i++)
    {
        game->enemies[i]->render(game->enemies[i]);
    }
    for (int i = 0; i < MAX_ENEMY_BULLETS; i++)
    {
        renderEnemyBullet(&game->enemy_bullets[i]);
    }

    // Mostrar vidas del jugador
    printf("\033[%d;%dHLIVES: %d\n", FIELD_HEIGHT + 3, 0, game->ship.lives);

    // Mostrar mensaje de fin de juego si es necesario
    if (game->game_over)
    {
        printf("\033[%d;%dHGame Over\n", FIELD_HEIGHT / 2, FIELD_WIDTH / 2 - 4);
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
