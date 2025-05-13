#include <utils/hello.h>
  int server_escuchar(t_log* logger,int socket_servidor);
int main(int argc, char* argv[]) {
    saludar("memoria");
  
    t_log *logger = log_create("memoria.log", "MEMORIA", true, LOG_LEVEL_INFO); // Crea .log
    t_config* config = config_create("memoria.config"); //lee el .config
    char* puerto_memoria = config_get_string_value(config, "PUERTO_MEMORIA");
    char* ip_memoria = config_get_string_value(config, "IP_MEMORIA");
    int puerto = config_get_int_value(config, "PUERTO_MEMORIA");
    int soket_memoria = iniciar_servidor(logger, ip_memoria, puerto_memoria);
    server_escuchar(logger, soket_memoria);
    printf("%d", puerto);
    // esperar_conexion(puerto, "MEMORIA_KERNEL", logger);
    // shutdown(puerto,SHUT_RDWR);
    // esperar_conexion(puerto, "MEMORIA_CPU", logger);
   

    /*int servidor = iniciar_servidor(puerto, logger);

    if (servidor == -1) {
        log_error(logger, "No se pudo iniciar servidor");
        return EXIT_FAILURE;
    }

    while (1) {
        aceptar_conexion(servidor, logger, "MEMORIA");
    }*/

    


    // int servidor = socket(AF_INET, SOCK_STREAM, 0);
    // struct sockaddr_in direccion;
    // direccion.sin_family = AF_INET;
    // direccion.sin_addr.s_addr = INADDR_ANY;
    // direccion.sin_port = htons(puerto);

    // bind(servidor, (void*)&direccion, sizeof(direccion));
    // listen(servidor, 10);

    // log_info(logger, "Memoria escuchando en puerto %d", puerto);
   
    // while(1) {
    //     log_info(logger, "me meti en el while %d", puerto);
        


    //     int cliente = accept(servidor, NULL, NULL);
    //     log_info(logger, "Nueva conexion aceptada");

    // }

    config_destroy(config);
    log_destroy(logger);

    return 0;
}
 int server_escuchar(t_log* logger,int socket_servidor) {
	char* server_name = "Memoria";
	int cliente_socket = esperar_cliente(logger,"memroira", socket_servidor);

	if (cliente_socket != -1) {
		//pthread_t hilo;
		int *args = malloc(sizeof(int));
		args = &cliente_socket;
		//pthread_create(&hilo, NULL, (void*) procesar_conexion, (void*) args);
		//pthread_detach(hilo);
		return 1;
	}
 }