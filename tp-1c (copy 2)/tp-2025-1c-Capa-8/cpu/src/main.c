#include <utils/hello.h>


int inicializarcpu(char** ip_kernel,char** ip_memoria, char** puerto_dispatch, int* puerto_interrupt,int* puerto_memoria, t_config* config);

int main(int argc, char* argv[]) {

    if (argc != 2) {
        printf("Uso: %s [identificador_cpu]\n", argv[0]);
        return EXIT_FAILURE;
    }


    char* id = argv[1];

    t_log* logger = log_create("cpu.log", "CPU", true, LOG_LEVEL_INFO); //Crea el .log
    t_config* config = config_create("config/cpu.config"); //lee el .config
    
    int cpu = 1;
    printf("hola %d", cpu); //test cpu

    
    char* ip_kernel;
    char* ip_memoria;
    char* puerto_dispatch;
    int puerto_interrupt, puerto_memoria;
    inicializarcpu(&ip_kernel,&ip_memoria,&puerto_dispatch,&puerto_interrupt,&puerto_memoria, config);
    log_info(logger, "pase el la config %s", puerto_dispatch);
    
    // HANDSHAKE KERNEL
    int sock_dispatch = crear_conexion(logger, ip_kernel, puerto_dispatch);
    char* momo = "anasheeeeeeeeeeeee";
    enviar_mensaje(ip_kernel, sock_dispatch);
    
    log_info(logger,"mensjae1");
    sleep(1);
    log_info(logger,"mensjae2");
    enviar_mensaje(momo,sock_dispatch);
    
    
    // shutdown(sock_dispatch,SHUT_RDWR);
    
    /*int sock_memoria = conectar(ip_memoria, puerto_memoria);
    send(sock_memoria, &size, sizeof(uint32_t), 0 );
    send(sock_memoria, id, size, 0);*/
    // shutdown(sock_memoria,SHUT_RDWR);

    /*int sock_interrupt = conectar(ip_kernel, puerto_interrupt);
    send(sock_interrupt, &size, sizeof(uint32_t), 0);
    send(sock_interrupt, id, size, 0);*/
    // shutdown(sock_interrupt,SHUT_RDWR);
    

   // log_info(logger, "CPU '%s' conectada al Kernel por dispatch (%d) e interrupt (%d)", id, puerto_dispatch, puerto_interrupt);

    //while (1) pause();

    return 0;
}
int inicializarcpu(char** ip_kernel,char** ip_memoria, char** puerto_dispatch, int* puerto_interrupt,int* puerto_memoria, t_config* config){
    *ip_kernel = config_get_string_value(config, "IP_KERNEL");
    *ip_memoria = config_get_string_value(config, "IP_MEMORIA");
    *puerto_dispatch = config_get_string_value(config, "PUERTO_KERNEL_DISPATCH");
    *puerto_interrupt = config_get_int_value(config, "PUERTO_KERNEL_INTERRUPT");
    *puerto_memoria = config_get_int_value(config, "PUERTO_MEMORIA");
    return 0; 
}