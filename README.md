# Gestión-Concurrente-de-una-Balsa-con-Procesos-y-Semáforos-
Este proyecto implementa una solución de sincronización de procesos utilizando memoria compartida y semáforos en C para simular la gestión de una balsa que transporta camiones. El objetivo principal es garantizar un acceso controlado y sincronizado a la balsa para evitar condiciones de carrera y mantener la consistencia de los recursos compartidos.

Memoria Compartida:
Se utiliza para almacenar la cantidad de espacios ocupados en la balsa, permitiendo que múltiples procesos puedan leer y modificar esta información.

Semáforos:
Dos semáforos permiten la sincronización entre el proceso padre (que representa la llegada de camiones) y el proceso hijo (que gestiona la partida y regreso de la balsa).

Semáforo 0: Controla el acceso a la memoria compartida (mutex).
Semáforo 1: Señaliza cuando la balsa está llena y lista para partir.
Aleatoriedad de Carga:
Cada camión que intenta subir a la balsa tiene un tamaño aleatorio de 1 o 2 espacios. El programa verifica si hay suficiente capacidad antes de aceptar el camión.

Salida Informativa:
El programa imprime mensajes claros que indican:

El momento en que un camión sube a la balsa.
Si la balsa está llena y parte hacia su destino.
El regreso de la balsa vacía para continuar con nuevas cargas.
Interacción de Procesos:
El padre y el hijo ejecutan tareas concurrentemente, mostrando cómo se gestionan los recursos de forma sincronizada para evitar inconsistencias.

Compilación y Ejecución:
bash
Copiar código
gcc -o balsa_proceso balsa.c -lpthread
./balsa_proceso
(Nota: La opción -lpthread es opcional si tu sistema no requiere explícitamente enlazar librerías POSIX).

Requisitos:
Sistema Linux/Unix compatible.
Conocimientos básicos de memoria compartida y semáforos.

Créditos: BRIZUELA AGUSTIN, DIETZ ROCIO, GAMBOA TOMAS.
