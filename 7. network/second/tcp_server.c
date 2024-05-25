#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>

#define port 8080
#define BUFFER_SIZE 1024

void handle_client(int client_socket) {
    char buffer[BUFFER_SIZE];
    int read_size;

    while ((read_size = recv(client_socket, buffer, BUFFER_SIZE, 0)) > 0) {
        send(client_socket, buffer, read_size, 0);
    }

    close(client_socket);
}

int main() {
    int server_socket, client_socket;
    struct sockaddr_in server_addr, client_addr;
    socklen_t client_addr_len = sizeof(client_addr);
    pid_t pid;

    if ((server_socket = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        perror("Socket create error");
        exit(EXIT_FAILURE);
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(port);

    if (bind(server_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("Server bind error");
        close(server_socket);
        exit(EXIT_FAILURE);
    }

    if (listen(server_socket, 10) < 0) {
        perror("Listen error");
        close(server_socket);
        exit(EXIT_FAILURE);
    }

    printf("TCP-server started. Listened port: %d\n", port);

    while ((client_socket = accept(server_socket, (struct sockaddr *)&client_addr, &client_addr_len)) >= 0) {
        printf("New connection %s:%d\n", inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));

        if ((pid = fork()) == 0) {
            close(server_socket);
            handle_client(client_socket);
            exit(0);
        } else if (pid < 0) {
            perror("Create process error");
        }
        close(client_socket);
    }

    if (client_socket < 0) {
        perror("Accept connection error");
        close(server_socket);
        exit(EXIT_FAILURE);
    }
    close(server_socket);
    return 0;
}
