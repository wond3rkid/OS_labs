#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/un.h>

#define SOCKET_PATH "/tmp/echo_socket"
#define BUFFER_SIZE 1024

int main() {
    int client_socket;
    struct sockaddr_un server_addr;
    char buffer[BUFFER_SIZE];
    int bytes_read;

    client_socket = socket(AF_UNIX, SOCK_STREAM, 0);
    if (client_socket == -1) {
        perror("Socket error");
        exit(EXIT_FAILURE);
    }

    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sun_family = AF_UNIX;
    strncpy(server_addr.sun_path, SOCKET_PATH, sizeof(server_addr.sun_path) - 1);

    if (connect(client_socket, (struct sockaddr*)&server_addr, sizeof(server_addr)) == -1) {
        perror("Connect error");
        close(client_socket);
        exit(EXIT_FAILURE);
    }

    printf("Connected to echo server. Type messages and press Enter.\n");

    while (fgets(buffer, sizeof(buffer), stdin) != NULL) {
        write(client_socket, buffer, strlen(buffer));
        bytes_read = read(client_socket, buffer, sizeof(buffer) - 1);
        if (bytes_read > 0) {
            buffer[bytes_read] = '\0';
            printf("Echo: %s\n", buffer);
        } else {
            if (bytes_read == 0) {
                printf("Server closed the connection.\n");
            } else {
                perror("Read error");
            }
            break;
        }
    }
    close(client_socket);
    return 0;
}
