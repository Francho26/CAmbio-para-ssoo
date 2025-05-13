#ifndef ESTRUCTURAS_HILOS
#define ESTRUCTURAS_HILOS

#include <pthread.h>
#include <semaphore.h>
#include <commons/collections/list.h>

//STRUCTURAS
//---------------------------------------------------------------
typedef enum {
	NEW,
	READY,
	BLOCKED,
	EXEC,
	EXIT,
	SUSP_BLOKED,
	SUSP_READY
} estado_proceso;

typedef struct{
	int pid;
	int pc;
	int me[7];
	int mt[7];
	estado_proceso estado;
} pcb;
typedef struct{
	char* ip;
	t_log* logger;
	int puerto;
} argumentos_memoria;

t_list* cola_new;
t_list* cola_ready;
t_list* cola_exec;
t_list* cola_blocked;
t_list* cola_exit;
//-----------------------------------------------------------------

//SEMAFOROS
//-------------------------------------------------------------------------
pthread_mutex_t mutex_cola_new;
pthread_mutex_t mutex_cola_ready;
pthread_mutex_t mutex_cola_exec;
pthread_mutex_t mutex_cola_blocked;
pthread_mutex_t mutex_cola_exit;

sem_t sem_procesos_en_ready;
//----------------------------------------------------------------------------

#endif