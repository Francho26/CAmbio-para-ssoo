#include <utils/hello.h>

#define HANDSHAKE_IO 0xCAFEBABE

int conectar(char* ip, int puerto);

int main(int argc, char* argv[]) {
    if (argc != 2) {
        printf("Uso: %s [nombre_dispositivo]\n", argv[0]);
        return EXIT_FAILURE;
    }

    char* nombre_dispositivo = argv[1];

    // Leer config
    t_config* config = config_create("/home/utnso/Desktop/tp-1c/tp-2025-1c-Capa-8/io/io.config");
    if (!config) {
        printf("No se pudo abrir io.config\n");
        return EXIT_FAILURE;
    }
     
    char* ip_kernel = config_get_string_value(config, "IP_KERNEL");
    int puerto_kernel = config_get_int_value(config, "PUERTO_ESCUCHA_IO");

    // Crear log
    t_log* logger = log_create("io.log", "IO", true, LOG_LEVEL_INFO);
    log_info(logger, "Dispositivo IO '%s' iniciando...", nombre_dispositivo);

    // Conectarse al Kernel
    int socket_kernel = conectar(ip_kernel, puerto_kernel);
    if (socket_kernel == -1) {
        log_error(logger, "Fallo la conexión con el Kernel.");
        return EXIT_FAILURE;
    }


    log_info(logger, "Conectado al Kernel en %s:%d", "ip_kernel", puerto_kernel);

    // Enviar handshake (nombre del dispositivo)
    uint32_t size = strlen(nombre_dispositivo) + 1;
    send(socket_kernel, &size, sizeof(uint32_t), 0);
    send(socket_kernel, nombre_dispositivo, size, 0);

    log_info(logger, "Handshake enviado con nombre: %s", nombre_dispositivo);

    // Simulación básica: espera eterna



    
    log_info(logger, "IO listo. Esperando peticiones...");

    while (1) pause();
    
    log_info(logger, "Paso el while");


    // Cleanup (nunca llega acá pero por convención)
    close(socket_kernel);
    config_destroy(config);
    log_destroy(logger);

    return EXIT_SUCCESS;
}



