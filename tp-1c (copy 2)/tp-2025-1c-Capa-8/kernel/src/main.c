#include <utils/hello.h>
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
#include <include/kernel.h>
// int conectar(char* ip, int puerto);
void* conectarconmemoria(void* args);

int main(int argc, char* argv[]) {

    
    t_log* logger = log_create("kernel.log", "KERNEL", true, LOG_LEVEL_INFO); //Crea el .log
    t_config* config = config_create("kernel.config"); //lee el .config
  

    
    
    if(logger == NULL){
        perror("ERROR - NO HAY LOGGER"); //Mensaje de error
        return 1;
    } //Verifica que el log tenga un valor    
    
    if(config == NULL){
        perror("ERROR - NO HAY CONFIG");//Mensaje de error
        return 1;
    } //Verifica que el config tenga un valor

    saludar("kernel"); //Verificacion

//colas de planificacion
    /*t_list* cola_new;
    t_list* cola_ready;
    t_list* cola_exec;
    t_list* cola_blocked;
    t_list* cola_exit;*/

//cracion semaforos y mutex
/*  pthread_mutex_t mutex_cola_new;
    pthread_mutex_t mutex_cola_ready;
    pthread_mutex_t mutex_cola_exec;    
    pthread_mutex_t mutex_cola_blocked;
    pthread_mutex_t mutex_cola_exit;

    sem_t sem_procesos_en_ready; */

//colas



    int puerto_io = config_get_int_value(config, "PUERTO_ESCUCHA_IO"); //Espera IO
    char* ip_memoria = config_get_string_value(config, "IP_MEMORIA"); // Recibe IO
    char* puerto_memoria = config_get_string_value(config, "PUERTO_MEMORIA"); //Espera memoria
    char* puerto_interrupt = config_get_string_value(config, "PUERTO_ESCUCHA_INTERRUPT"); //Espera CPU - Interrupt
    char* puerto_dispatch = config_get_string_value(config, "PUERTO_ESCUCHA_DISPATCH"); //Espera CPU -Dispatch*/
    char* ip_CPU = config_get_string_value(config, "IP_CPU"); // Recibe IO

    printf("hola %s",puerto_dispatch);
    
    log_info(logger, "lei %s",puerto_dispatch);
    //------------------------------
    int soket_servidor = iniciar_servidor(logger,ip_memoria,puerto_memoria);
    ///esperar_cliente(logger,"memoria",soket_servidor);
    crear_conexion(logger,ip_memoria,puerto_memoria);
    //------------------------------
    int sokert_dispache_cpu=  iniciar_servidor(logger,ip_CPU,puerto_dispatch);
    int soket_dispatch = esperar_cliente(logger,"Cpu",sokert_dispache_cpu);
    //crear_conexion(logger,ip_CPU,puerto_dispatch);
    
    recibir_mensaje(logger, soket_dispatch);
    
    recibir_mensaje(logger, soket_dispatch);

    // log_info(logger, "Kernel esta activo %d");
    // log_info(logger, puerto_io);
   // pthread_t hilo_memoria;
   /* argumentos_memoria* data = malloc(sizeof(argumentos_memoria));
    data->ip = ip_memoria;
    data->logger = logger;
    data->puerto = puerto_memoria;*/
    //------------------------------------------------------------------------------------------
    /* MODULO MEMORIA */
    /*pthread_create(&hilo_memoria,NULL,conectarconmemoria,data);
    pthread_join(hilo_memoria,NULL);
    free(data);*/

    
    //int servidor_dispatch = iniciar_servidor(puerto_dispatch, logger);
    //int servidor_interrupt = iniciar_servidor(puerto_interrupt, logger);
    
    /*if (servidor_dispatch == -1) {
        log_error(logger, "No se pudo iniciar servidor");
        return EXIT_FAILURE;
    }*/

    //aceptar_conexion(servidor_dispatch, logger, "DISPATCH");
    //aceptar_conexion(servidor_interrupt, logger, "INTERRUPT");
    //esperar_conexion(puerto_io,"IO", logger);
    config_destroy(config);
    log_destroy(logger);
    
    return 0;
} 

    


// int conectar(char* ip, int puerto) {

//     int socket_io = socket(AF_INET, SOCK_STREAM, 0);
//     if (socket_io == -1)
//       return -1;


//     struct sockaddr_in direccion;
//     direccion.sin_family = AF_INET;
//     direccion.sin_port = htons(puerto);
//     direccion.sin_addr.s_addr = inet_addr(ip);

//     if (connect(socket_io, (void *)&direccion, sizeof(direccion)) != 0)
//     {
//         close(socket_io);
//         return -1;
//     }

//     return socket_io;
// };

/*void* conectarconmemoria(void* arg){ 
    argumentos_memoria* args = (argumentos_memoria*) arg;
    int socket_memoria = conectar(args->ip, args->puerto);
    if (socket_memoria == -1) {
        log_error(args->logger, "Fallo la conexión con la memoria.");
        return EXIT_FAILURE;
    }

    log_info(args->logger, "Conectado al memoria en %s:%d", "ip_memoria", args->puerto);
     log_info(args->logger, "Memoria conectada. Esperando peticiones...");
    char* handshake = "KERNEL";
    uint32_t size = strlen(handshake) + 1;
    send(socket_memoria, &size, sizeof(uint32_t), 0);
    send(socket_memoria, handshake, size, 0);
    log_info(args->logger, "Handshake enviado con nombre: %s", "kernel");

}*/