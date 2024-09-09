#ifndef ENEMY_H
#define ENEMY_H

#define MAX_ENEMY_BULLETS 50

typedef struct NaveEnemiga NaveEnemiga;

// =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+
// ===========================  BULLET STRUCTS ============================
typedef struct
{
    int x;
    int y;
    int active;
} EnemyBullet;

// ============================  BULLET STRUCTS ===========================
// =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+

// =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+
// ======================= ALIENS SHIPS STRUCTS ===========================

typedef enum
{
    BASIC_TYPE,
    MOVING_TYPE,

    ENEMY_TYPE_COUNT = 2
} EnemyType;
typedef struct NaveEnemiga
{
    int x;
    int y;
    int active;
    EnemyType type;
    int size_in_mem;
    void (*update)(struct NaveEnemiga *);
    void (*render)(struct NaveEnemiga *);
    void (*fire)(struct NaveEnemiga *, EnemyBullet bullets[]);
    void (*moveDown)(struct NaveEnemiga *);
    void (*moveSide)(struct NaveEnemiga *); // Nueva función para movimiento lateral
} NaveEnemiga;

// typedef struct
// {
//     NaveEnemiga base; // NaveEnemiga como base
// } Enemy;

// typedef struct
// {
//     NaveEnemiga base; // NaveEnemiga como base
//     int direction;    // 1 para derecha, -1 para izquierda
// } MovingEnemy;

// ======================= ALIENS SHIPS STRUCTS ===========================
// =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+

// =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+
// ============================== FUNCTIONS ===============================

void initGeneralEnemy(NaveEnemiga *enemy);
void initEnemy(NaveEnemiga *enemy);
void initMovingEnemy(NaveEnemiga *enemy);
void updateEnemy(NaveEnemiga *enemy);
void renderEnemy(NaveEnemiga *enemy);
void fireEnemyBullet(NaveEnemiga *enemy, EnemyBullet bullets[]);
void moveEnemyDown(NaveEnemiga *enemy);
void moveEnemySide(NaveEnemiga *enemy); // Nueva función

void initEnemyBullet(EnemyBullet *bullet);
void updateEnemyBullet(EnemyBullet *bullet);
void renderEnemyBullet(EnemyBullet *bullet);

// ============================== FUNCTIONS ===============================
// =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+

#endif