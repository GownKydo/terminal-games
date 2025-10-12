#include <iostream>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#define SERVER_IP "127.0.0.1" // IP del servidor (localhost para pruebas)
#define PORT 8080 // Puerto del servidor

void startClient() {
    int sock = 0;
    struct sockaddr_in serv_addr;
    
    // Crear el socket
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("No se pudo crear el socket");
        return;
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    // Convertir la IP a formato binario
    if (inet_pton(AF_INET, SERVER_IP, &serv_addr.sin_addr) <= 0) {
        perror("Dirección no válida");
        return;
    }
    
    // Conectar al servidor
    if (connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0) {
        perror("Conexión fallida");
        return;
    }
    
    std::cout << "Conectado al servidor. ¡Listo para jugar!\n";
    
    char buffer[1024];
    
    while (true) {
        std::cout << "Introduce una letra: ";
        std::string letter;
        std::cin >> letter;
        
        if (letter.length() == 1) {
            // Enviar la letra al servidor
            send(sock, letter.c_str(), letter.length(), 0);
            
            // Recibir la respuesta del servidor
            int valread = read(sock, buffer, sizeof(buffer));
            if (valread > 0) {
                std::cout << "Respuesta del servidor: " << buffer << std::endl;
            }
        } else {
            std::cout << "Por favor, introduce solo una letra.\n";
        }
    }
    
    close(sock);
}
