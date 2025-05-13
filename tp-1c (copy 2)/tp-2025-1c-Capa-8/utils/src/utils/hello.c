#include <utils/hello.h>

void saludar(char* quien) {
    printf("Hola desde %s!!\n", quien);
};

int iniciar_servidor(t_log* logger, char* ip, char* puerto)
{
	int socket_servidor;

	struct addrinfo hints, *servinfo;

	memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = AI_PASSIVE;

	getaddrinfo(ip, puerto, &hints, &servinfo);

	// Creamos el socket de escucha del servidor

	socket_servidor = socket(servinfo->ai_family, servinfo->ai_socktype, servinfo->ai_protocol);

	// Asociamos el socket a un puerto

	bind(socket_servidor, servinfo->ai_addr, servinfo->ai_addrlen);

	// Escuchamos las conexiones entrantes

	listen(socket_servidor, SOMAXCONN);

	log_info(logger, "Listo para escuchar a mi cliente");

	freeaddrinfo(servinfo);

	return socket_servidor;
}
int esperar_cliente(t_log* logger, const char* name, int socket_servidor) {
    struct sockaddr_in dir_cliente;
    socklen_t tam_direccion = sizeof(struct sockaddr_in);

    int socket_cliente = accept(socket_servidor, (void*) &dir_cliente, &tam_direccion);
    if (socket_cliente == -1) {
		log_error(logger, "Error al aceptar cliente en %s", socket_servidor);
		return -1;
	}
    log_info(logger, "Cliente conectado a %s", name);

    return socket_cliente;
}


int crear_conexion(t_log* logger, char* ip, char* puerto) {
    struct addrinfo hints, *servinfo;

    // Init de hints
    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;

    // Recibe addrinfo
    getaddrinfo(ip, puerto, &hints, &servinfo);

    // Crea un socket con la informacion recibida (del primero, suficiente)
    int socket_cliente = socket(servinfo->ai_family, servinfo->ai_socktype, servinfo->ai_protocol);

    // Fallo en crear el socket
    if(socket_cliente == -1) {
        log_error(logger, "Error creando el socket para %s:%s", ip, puerto);
        return 0;
    }

    // Error conectando
    if(connect(socket_cliente, servinfo->ai_addr, servinfo->ai_addrlen) == -1) {
        log_error(logger, "Error al conectar \n");
        freeaddrinfo(servinfo);
        return 0;
    } else
        log_info(logger, "Cliente conectado en %s:%s\n", ip, puerto);

    freeaddrinfo(servinfo); //free

    return socket_cliente;
}

// CERRAR CONEXION
void liberar_conexion(int* socket_cliente) {
    close(*socket_cliente);
    *socket_cliente = -1;
}
