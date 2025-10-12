#include <iostream>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include "hangman.h"

#define PORT 8080

void startServer() {
    int server_fd, clientSocket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    char buffer[1024];
    int valread;

    // Crear el socket
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("No se pudo crear el socket");
        exit(EXIT_FAILURE);
    }

    // Configurar la dirección del servidor
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    // Vincular el socket
    if (bind(server_fd, (struct sockaddr*)&address, sizeof(address)) < 0) {
        perror("Error en el bind");
        exit(EXIT_FAILURE);
    }

    // Escuchar por conexiones entrantes
    if (listen(server_fd, 3) < 0) {
        perror("Error en el listen");
        exit(EXIT_FAILURE);
    }

    std::cout << "Esperando conexiones en el puerto " << PORT << "...\n";

    // Esperar y aceptar conexiones de clientes
    while (true) {
        if ((clientSocket = accept(server_fd, (struct sockaddr*)&address, (socklen_t*)&addrlen)) < 0) {
            perror("Error en el accept");
            exit(EXIT_FAILURE);
        }

        std::cout << "Cliente conectado.\n";

        // Manejar la comunicación con el cliente
        while (true) {
            memset(buffer, 0, sizeof(buffer));  // Limpiar el buffer
            valread = read(clientSocket, buffer, sizeof(buffer));  // Leer datos del cliente

            if (valread <= 0) {
                std::cout << "El cliente ha cerrado la conexión o ha habido un error.\n";
                break;  // Salir si el cliente desconecta o hay error
            }

            std::string letter(buffer);  // Obtener la letra enviada por el cliente
            std::cout << "Cliente envió: " << letter << std::endl;

            bool isCorrect = false;  // Aquí debe ir la lógica para comprobar si la letra es correcta
            // Si la letra es correcta o incorrecta, enviar la respuesta al cliente
            const char* response = isCorrect ? "Letra correcta!" : "Letra incorrecta!";
            send(clientSocket, response, strlen(response), 0);
        }

        close(clientSocket);  // Cerrar la conexión con el cliente
    }

    close(server_fd);  // Cerrar el socket del servidor
}
