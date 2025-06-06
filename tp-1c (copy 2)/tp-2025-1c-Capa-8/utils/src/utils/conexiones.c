#include <utils/hello.h>
#include <assert.h>
void enviar_mensaje(char* mensaje, int socket_cliente){
	t_paquete* paquete = malloc(sizeof(t_paquete));
    
	paquete->codigo_operacion = MENSAJE;
	paquete->buffer = malloc(sizeof(t_buffer));
	paquete->buffer->size = strlen(mensaje) + 1;

	paquete->buffer->stream = malloc(paquete->buffer->size);
  
	memcpy(paquete->buffer->stream, mensaje, paquete->buffer->size);
    
	int bytes = paquete->buffer->size + 2*sizeof(int);

	void* a_enviar = serializar_paquete(paquete, bytes);

	send(socket_cliente, a_enviar, bytes, 0);
    
	free(a_enviar);
	eliminar_paquete(paquete);
}

void* serializar_paquete(t_paquete* paquete, int bytes){
	void * magic = malloc(bytes);
	int desplazamiento = 0;

	memcpy(magic + desplazamiento, &(paquete->codigo_operacion), sizeof(int));
	desplazamiento+= sizeof(int);
	memcpy(magic + desplazamiento, &(paquete->buffer->size), sizeof(int));
	desplazamiento+= sizeof(int);
	memcpy(magic + desplazamiento, paquete->buffer->stream, paquete->buffer->size);
	desplazamiento+= paquete->buffer->size;

	return magic;
}
void eliminar_paquete(t_paquete* paquete){
	free(paquete->buffer->stream);
	free(paquete->buffer);
	free(paquete);
}

void recibir_mensaje(t_log* logger, int socket_cliente){
	int size;
	char* buffer = recibir_buffer(&size, socket_cliente);
	log_info(logger, "Me llego el mensaje: %s", buffer);
	free(buffer);
}

void* recibir_buffer(int* size, int socket_cliente){
	void * buffer;
	int codigodeoperacion;

	if(recv(socket_cliente, &codigodeoperacion, sizeof(int), MSG_WAITALL)<=0){
		perror("mal code op");
		return EXIT_FAILURE;
	}
	if(recv(socket_cliente, size, sizeof(int), MSG_WAITALL)<=0){
		perror("mal size");
		return EXIT_FAILURE;
	}
	buffer=malloc(*size);

	if(recv(socket_cliente, buffer, *size, MSG_WAITALL)<=0){
		perror("mal buffer");
		return EXIT_FAILURE;
	}
	/*if(recv(socket_cliente, size, sizeof(int), MSG_WAITALL)==-1){
		perror("no recibio bien");
		return EXIT_FAILURE;
	}*/
	
	//buffer = malloc(*size);
	//recv(socket_cliente, buffer, *size, MSG_WAITALL);

	return buffer;
}