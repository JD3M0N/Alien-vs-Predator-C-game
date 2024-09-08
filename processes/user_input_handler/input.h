#ifndef INPUT
#define INPUT

#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>
#include <pthread.h>
#include "global_signals.h"
#include "../../Game Code/terminal_input.h"

#define Buffer_Size 100

extern char buffer[Buffer_Size];
extern char valid_keys[3];
extern char user_input_fr;
extern int buffer_index;

extern pthread_mutex_t mutex_buffer;
extern pthread_cond_t can_read;
extern pthread_cond_t can_consume;

void *get_input(void *arg);
void *consume_input(void *arg);
void user_input_handler();

#endif
