#ifndef GLOBAL_SIGNALS
#define GLOBAL_SIGNALS

#include <pthread.h>

extern pthread_cond_t can_do_logic;
extern pthread_cond_t can_render;
extern pthread_cond_t can_change_ship;

extern pthread_mutex_t board_mutex;
extern pthread_mutex_t global_mutex;
extern pthread_mutex_t user_ship;

#endif
