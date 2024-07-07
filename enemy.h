#ifndef ENEMY_H
#define ENEMY_H

#define MAX_ENEMY_BULLETS 10

typedef struct
{
    int x;
    int y;
} Enemy;

typedef struct
{
    int x;
    int y;
    int active;
} EnemyBullet;

void initEnemy(Enemy *enemy);
void updateEnemy(Enemy *enemy);
void renderEnemy(Enemy *enemy);

void initEnemyBullet(EnemyBullet *bullet);
void fireEnemyBullet(EnemyBullet bullets[], Enemy *enemy);
void updateEnemyBullet(EnemyBullet *bullet);
void renderEnemyBullet(EnemyBullet *bullet);

#endif