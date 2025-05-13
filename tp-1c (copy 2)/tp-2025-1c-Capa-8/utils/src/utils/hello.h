#ifndef UTILS_HELLO_H_
#define UTILS_HELLO_H_

#include <stdlib.h>
#include <stdio.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <commons/config.h>
#include <commons/log.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <netinet/in.h>
#include <unistd.h>
#include <netdb.h>

/**
* @brief Imprime un saludo por consola
* @param quien Módulo desde donde se llama a la función
* @return No devuelve nada
*/
typedef enum
{
	MENSAJE,
	PAQUETE
}op_code;
typedef struct
{
	int size;
	void* stream;
} t_buffer;
typedef struct
{
	op_code codigo_operacion;
	t_buffer* buffer;
} t_paquete;

typedef struct
{
	char* mensaje;
	int puerto;
}argumento_mensaje;


int iniciar_servidor(t_log* logger, char* ip, char* puerto);
int crear_conexion(t_log* logger, char* ip, char* puerto);
void liberar_conexion(int* socket_cliente);
int esperar_cliente(t_log* logger, const char* name, int socket_servidor);


int conectar(char* ip, int puerto);
void saludar(char* quien);
int esperar_conexion(int puerto,  char* nombre, t_log* logger);
//int esperar_cliente(int socket_servidor);
void* serializar_paquete(t_paquete* paquete, int bytes);
void enviar_mensaje(char* mensaje, int socket_cliente);
void eliminar_paquete(t_paquete* paquete);
void recibir_mensaje( t_log* logger ,int socket_cliente);
void* recibir_buffer(int* size, int socket_cliente);
/*void enviar_mensaje(char* mensaje, int socket_cliente);*/

//int iniciar_servidor(int puerto, t_log* logger);
int aceptar_conexion(int servidor, t_log* logger, char* nombre);
//int crear_conexion(char *ip, char *puerto);
 #endif 