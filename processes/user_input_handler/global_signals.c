#include "global_signals.h"

pthread_cond_t can_do_logic = PTHREAD_COND_INITIALIZER;
pthread_cond_t can_render = PTHREAD_COND_INITIALIZER;
pthread_cond_t can_change_ship = PTHREAD_COND_INITIALIZER;

pthread_mutex_t board_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t global_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t user_ship = PTHREAD_MUTEX_INITIALIZER;
