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
struct NaveEnemiga
{
    int x;
    int y;
    int active;
    void (*update)(NaveEnemiga *enemy);
    void (*render)(NaveEnemiga *enemy);
    void (*fire)(NaveEnemiga *enemy, EnemyBullet bullets[]);
};

typedef struct
{
    NaveEnemiga base; // NaveEnemiga como base
} Enemy;

typedef struct
{
    NaveEnemiga base; // NaveEnemiga como base
    int direction;    // 1 para derecha, -1 para izquierda
} MovingEnemy;
// ======================= ALIENS SHIPS STRUCTS ===========================
// =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+

// =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+
// ============================== FUNCTIONS ===============================

void initEnemy(Enemy *enemy);
void updateEnemy(NaveEnemiga *enemy);                            // Cambia el tipo de argumento a NaveEnemiga
void renderEnemy(NaveEnemiga *enemy);                            // Cambia el tipo de argumento a NaveEnemiga
void fireEnemyBullet(NaveEnemiga *enemy, EnemyBullet bullets[]); // Cambia el tipo de argumento a NaveEnemiga

// Funciones para MovingEnemy
void initMovingEnemy(MovingEnemy *enemy);
void updateMovingEnemy(NaveEnemiga *enemy);                            // Cambia el tipo de argumento a NaveEnemiga
void renderMovingEnemy(NaveEnemiga *enemy);                            // Cambia el tipo de argumento a NaveEnemiga
void fireMovingEnemyBullet(NaveEnemiga *enemy, EnemyBullet bullets[]); // Cambia el tipo de argumento a NaveEnemiga

// void initEnemyBullet(EnemyBullet *bullet);
// void fireEnemyBullet(EnemyBullet bullets[], Enemy *enemy);
// void updateEnemyBullet(EnemyBullet *bullet);
// void renderEnemyBullet(EnemyBullet *bullet);

// ============================== FUNCTIONS ===============================
// =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+

#endif