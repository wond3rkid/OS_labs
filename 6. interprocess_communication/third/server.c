#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <signal.h>
#include <stdlib.h>
#include <sys/wait.h>

#define SOCKET_PATH "/tmp/echo_socket"
#define BUFFER_SIZE 1024

int server_socket;

void handle_client(int client_socket) {
    char buffer[BUFFER_SIZE];
    int bytes_read;

    while ((bytes_read = read(client_socket, buffer, sizeof(buffer) - 1)) > 0) {
        buffer[bytes_read] = '\0';
        printf("Received from client: %s\n", buffer);
        write(client_socket, buffer, bytes_read);
    }
    if (bytes_read == -1) {
        perror("Read error. Client disconnected \n");
    }
    close(client_socket);
}


void sigchld_handler(int sig) {
    while (waitpid(-1, NULL, WNOHANG) > 0);
}

void handle_sigint(int sig) {
    const char *msg = "Caught signal. Terminated...\n";
    write(STDOUT_FILENO, msg, strlen(msg));
    close(server_socket);
    unlink(SOCKET_PATH);
    _exit(0);
}

void main() {
    struct sockaddr_un server_addr, client_addr;
    socklen_t client_addr_len = sizeof(client_addr);

    signal(SIGINT, handle_sigint);
    struct sigaction sa;
    sa.sa_handler = sigchld_handler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_RESTART;
    if (sigaction(SIGCHLD, &sa, NULL) == -1) {
        perror("sigaction");
        exit(EXIT_FAILURE);
    }
    server_socket = socket(AF_UNIX, SOCK_STREAM, 0);
    if (server_socket == -1) {
        perror("Socket create error");
        exit(1);
    }

    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sun_family = AF_UNIX;
    strncpy(server_addr.sun_path, SOCKET_PATH, sizeof(server_addr.sun_path) - 1);

    unlink(SOCKET_PATH);
    if (bind(server_socket, (struct sockaddr *) &server_addr, sizeof(server_addr)) == -1) {
        perror("Bind error");
        close(server_socket);
        exit(1);
    }

    if (listen(server_socket, 5) == -1) {
        perror("Listen error");
        close(server_socket);
        exit(1);
    }

    fprintf(stdout, "Echo server is listening...\n");

    while (1) {
        int client_socket = accept(server_socket, (struct sockaddr *) &client_addr, &client_addr_len);
        if (client_socket == -1) {
            perror("Accept error");
            continue;
        }

        if (fork() == 0) {
            close(server_socket);
            handle_client(client_socket);
            exit(0);
        } else {
            close(client_socket);
        }
    }
}
