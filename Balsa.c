#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <unistd.h>
#include <wait.h>

#define CAPACIDAD_BALSA 9
#define CLAVE_SEMAFORO 1234
#define CLAVE_MEMORIA_COMPARTIDA 5678

struct Balsa {
    int espacios_ocupados;
};

void modificar_semaforo(int id_semaforo, int num_semaforo, int operacion);
void print_info_grupo();

int main() {

print_info_grupo();

    int id_memoria_compartida = shmget(CLAVE_MEMORIA_COMPARTIDA, sizeof(struct Balsa), IPC_CREAT | 0666);
    if (id_memoria_compartida == -1) {
        perror("Error al crear memoria compartida");
        exit(1);
    }

    struct Balsa *balsa = (struct Balsa *)shmat(id_memoria_compartida, NULL, 0);
    if (balsa == (void *)-1) {
        perror("Error al adjuntar memoria compartida");
        exit(1);
    }
    balsa->espacios_ocupados = 0;

    int id_semaforo = semget(CLAVE_SEMAFORO, 2, IPC_CREAT | 0666);
    if (id_semaforo == -1) {
        perror("Error al crear semáforos");
        exit(1);
    }

    semctl(id_semaforo, 0, SETVAL, 1); 
    semctl(id_semaforo, 1, SETVAL, 0); 
    pid_t proceso_hijo = fork();

    if (proceso_hijo == 0) { 
        while (1) {
            modificar_semaforo(id_semaforo, 1, -1); 
            printf("La balsa está llena y parte hacia su destino.\n");
            modificar_semaforo(id_semaforo, 0, -1); 
            balsa->espacios_ocupados = 0;
            printf("La balsa ha regresado vacía.\n");
            modificar_semaforo(id_semaforo, 0, 1); 
        }
    } else { 
        while (1) {
            int tamanio_camion = rand() % 2 + 1; 
            modificar_semaforo(id_semaforo, 0, -1); 
            if (balsa->espacios_ocupados + tamanio_camion <= CAPACIDAD_BALSA) {
                balsa->espacios_ocupados += tamanio_camion;
                printf("Camión (%d espacio/s) subió. Espacios ocupados: %d/%d\n", tamanio_camion, balsa->espacios_ocupados, CAPACIDAD_BALSA);
                if (balsa->espacios_ocupados == CAPACIDAD_BALSA) {
                    printf("La balsa está lista para partir.\n");
                    modificar_semaforo(id_semaforo, 1, 1); 
                }
            } else {
                printf("No hay espacio suficiente para un camión de %d espacio/s.\n", tamanio_camion);
            }
            modificar_semaforo(id_semaforo, 0, 1); 
            sleep(1);
        }
    }
    return 0;
}

void modificar_semaforo(int id_semaforo, int num_semaforo, int operacion) {
    struct sembuf operacion_semaforo;
    operacion_semaforo.sem_num = num_semaforo;
    operacion_semaforo.sem_op = operacion;
    operacion_semaforo.sem_flg = 0;
    semop(id_semaforo, &operacion_semaforo, 1);
}
void print_info_grupo() {
    printf("=====================================================================\n");
    printf("Grupo: 54\n");
    printf("Integrantes:\n");
    printf("Nombre: Brizuela, Agustin | ");
    printf("Nombre: Dietz, Rocio | ");
    printf("Nombre: Gamboa, Tomas |");
    printf("=====================================================================\n\n");
}
