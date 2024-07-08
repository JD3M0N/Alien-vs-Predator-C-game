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

typedef struct
{
    int x;
    int y;
    int active;
    int direction; // 1 para derecha, -1 para izquierda
} MovingEnemy;

void initMovingEnemy(MovingEnemy *enemy);
void updateMovingEnemy(MovingEnemy *enemy);
void renderMovingEnemy(MovingEnemy *enemy);
void fireMovingEnemyBullet(EnemyBullet bullets[], MovingEnemy *enemy);

void initEnemy(Enemy *enemy);
void updateEnemy(Enemy *enemy);
void renderEnemy(Enemy *enemy);

void initEnemyBullet(EnemyBullet *bullet);
void fireEnemyBullet(EnemyBullet bullets[], Enemy *enemy);
void updateEnemyBullet(EnemyBullet *bullet);
void renderEnemyBullet(EnemyBullet *bullet);

#endif