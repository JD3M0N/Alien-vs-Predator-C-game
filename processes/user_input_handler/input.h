#ifndef INPUT
#define INPUT

#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include <unistd.h>
#include <stdbool.h>
#include <pthread.h>

#include "globlal_signals.h"

#define Buffer_Size 100
char buffer[Buffer_Size];
char valid_keys[3] = {'a', 'd', 'k'};

char user_input_fr;

int index = 0;

pthread_mutex_t mutex_buffer = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t can_read = PTHREAD_COND_INITIALIZER;
pthread_cond_t can_consume = PTHREAD_COND_INITIALIZER;

void *get_input(void *arg)
{

    char input = _getch();

    pthread_mutex_lock(&mutex_buffer);
    while (index == Buffer_Size)
        pthread_cond_wait(&can_read, &mutex_buffer);

    user_input_fr = input;
    index = 1; // Indicar que hay un nuevo input disponible

    pthread_cond_signal(&can_consume);
    pthread_mutex_unlock(&mutex_buffer);
}

void *consume_input(void *arg)
{

    pthread_mutex_lock(&mutex_buffer);
    pthread_mutex_lock(&user_ship);

    while (index == 0)
        pthread_cond_wait(&can_consume, &mutex_buffer);

    for (int i = 0; i < sizeof(valid_keys); i++)
    {
        if (user_input_fr == valid_keys[i])
        {
            pthread_cond_signal(&can_change_ship);
            break;
        }
    }

    index = 0; // Indicar que el input ha sido consumido
    pthread_cond_signal(&can_read);
    pthread_mutex_unlock(&mutex_buffer);
    pthread_mutex_unlock(&user_ship);
}

void user_input_handler()
{
    pthread_t get_input_tid, consume_input_tid;

    // Inicializar mutex
    mutex_buffer = PTHREAD_MUTEX_INITIALIZER;

    // Crear hilos productor y consumidor
    if (pthread_create(&get_input_tid, NULL, get_input, NULL) != 0)
    {
        perror("Error al crear el hilo de get_input");
        exit(EXIT_FAILURE);
    }

    if (pthread_create(&consume_input_tid, NULL, consume_input, NULL) != 0)
    {
        perror("Error al crear el hilo consume_input");
        exit(EXIT_FAILURE);
    }

    // Esperar a que los hilos terminen

    if (pthread_join(get_input_tid, NULL) != 0)
    {
        perror("Error al unir el get_input");
        exit(EXIT_FAILURE);
    }

    if (pthread_join(consume_input_tid, NULL) != 0)
    {
        perror("Error al unir el hilo consume_input");
        exit(EXIT_FAILURE);
    }

    // Liberar recursos
    pthread_cancel(get_input_tid);
    pthread_cancel(consume_input_tid);
    pthread_mutex_destroy(&mutex_buffer);

    // Liberar mutex_global
    pthread_mutex_unlock(&global_mutex);

    // Cuando esté implementado con procesos
    // exit(EXIT_SUCCESS);
}

#endif