
# MatComInvasion

**Autor**: Rodrigo Mederos y Josue R. Naranjo  
**Institución**: Facultad de Matemática y Computación  
**Curso**: Sistemas Operativos  
**Fecha**: Septiembre 09, 2024

## Introducción

En el marco del proyecto de Sistemas Operativos, se ha desarrollado *MatComInvasion*, un juego arcade estilo "Alien Invaders" programado en C. El juego tiene lugar en la Facultad de Matemática y Computación de la Universidad de La Habana, bajo ataque por una invasión alienígena. El objetivo es repeler a los invasores utilizando conceptos de sistemas operativos como programación orientada a eventos, concurrencia, gestión de memoria, y planificación de procesos.

## Funcionamiento del Juego

*MatComInvasion* es un juego arcade donde el jugador controla una nave espacial para defender la Tierra de invasores. Las acciones clave incluyen:
- **Actualización de la Nave del Jugador**: Movimiento lateral y disparo hacia arriba.
- **Gestión de Enemigos**: Las naves enemigas descienden y disparan hacia el jugador.
- **Detección de Colisiones**: Impacto de balas y eliminación de naves.
- **Rendimiento Gráfico**: Representación en consola.
- **Planificación y Gestión de Procesos**: Cada entidad del juego es tratada como un proceso independiente.
- **Condiciones de Fin del Juego**: El juego termina si las naves enemigas llegan al suelo o el jugador pierde todas sus vidas.

## Ejecución del Juego en Arch Linux

Para ejecutar el juego en Arch Linux, usa el comando `MatComInvasion` en la terminal. Esto se configura mediante un alias en un script de Bash:

```bash
alias MatComInvasion='cd /ruta/Project && ./game'
```

Este alias cambia al directorio del juego y ejecuta el archivo binario.

## Mejoras en la Gestión de Procesos y Memoria

1. **Creación Dinámica de Procesos**: Cada nave enemiga es un proceso independiente.
2. **Liberación de Procesos y Memoria**: Procesos eliminados cuando las naves son destruidas.
3. **Identificación de Procesos mediante Punteros**: Uso de punteros para gestionar procesos.
4. **Algoritmo de Reemplazo de Páginas**: Optimiza el uso de memoria.
5. **Gestión de Señales y Comunicación entre Procesos**: Coordinación efectiva entre entidades del juego.

## Creación Dinámica de Procesos

La creación y gestión de procesos se realiza mediante un administrador de procesos (`process-manager.c`), que utiliza colas de prioridad. Los procesos se crean con `fork()` y se gestionan con señales como `SIGSTOP` y `SIGCONT`. La eliminación de procesos se hace con `SIGKILL`.

## Gestión de Hilos en MatComInvasion

Los hilos en *MatComInvasion* gestionan la entrada del usuario y la actualización del juego. Se utiliza un patrón productor-consumidor con mutexes y variables de condición para la sincronización.

- **Captura de Entrada del Usuario**: Un hilo captura y almacena la entrada.
- **Procesamiento de la Entrada**: Otro hilo procesa la entrada y actualiza el juego.
- **Implementación del Manejador de Entrada**: Se crean y coordinan los hilos usando `pthread_create` y `pthread_join`.

El manejo de hilos permite una respuesta ágil y eficiente, garantizando un juego fluido en un entorno multitarea.

--- 

Este resumen proporciona una visión general de las secciones principales y sus componentes en el documento LaTeX.
