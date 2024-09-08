#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/mman.h>
#include "Game Code/process_table.h"  // Asegúrate de que esto está incluido correctamente

int main() {
    process_table = mmap(NULL, sizeof(ProcessTable), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    if (process_table == MAP_FAILED) {
        perror("mmap");
        exit(EXIT_FAILURE);
    }

    while (1) {
        printProcessTable();
        sleep(1); // Refrescar cada segundo
    }
    return 0;
}
