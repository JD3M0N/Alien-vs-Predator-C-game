#ifndef PROCESS_SCHEDULING_H
#define PROCESS_SCHEDULING_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include "../processes/user_input_handler/global_signals.h"

#define NUM_LEVELS 3

typedef struct {
    pid_t queue[NUM_LEVELS][MAX_PROCESSES];
    int front[NUM_LEVELS];
    int rear[NUM_LEVELS];
} MLFQ;

MLFQ mlfq;

void initMLFQ() {
    for (int i = 0; i < NUM_LEVELS; i++) {
        mlfq.front[i] = 0;
        mlfq.rear[i] = 0;
    }
}

void addProcessToQueue(pid_t pid, int level) {
    if (mlfq.rear[level] < MAX_PROCESSES) {
        mlfq.queue[level][mlfq.rear[level]++] = pid;
    }
}

void executeProcesses() {
    for (int level = 0; level < NUM_LEVELS; level++) {
        while (mlfq.front[level] < mlfq.rear[level]) {
            pid_t pid = mlfq.queue[level][mlfq.front[level]++];
            pthread_mutex_lock(&global_mutex);
            pthread_cond_signal(&can_do_logic);
            pthread_mutex_unlock(&global_mutex);
            // Wait for the process to finish its time slice
            usleep(100000); // Adjust time slice as needed
        }
    }
}

#endif
