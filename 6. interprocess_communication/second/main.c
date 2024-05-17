#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <unistd.h>
#include <stdbool.h>
#include <sys/wait.h>

int main() {
    int file_pipe[2];
    unsigned int send_value = 0;
    if (pipe(file_pipe) == -1) {
        perror("Pipe error");
        return EXIT_FAILURE;
    }
    pid_t pid = fork();
    if (pid == -1) {
        perror("Pid error");
        return EXIT_FAILURE;
    }
    if (pid == 0) {
        close(file_pipe[0]);
        while (true) {
            if (write(file_pipe[1], &send_value, sizeof(send_value)) == -1) {
                perror("Write to file pipe error");
                return EXIT_FAILURE;
            }
            send_value++;
        }
    } else {
        unsigned int received_value, expected_value = 0;
        close(file_pipe[1]);
        while (true) {
            if (read(file_pipe[0], &received_value, sizeof(received_value)) > 0) {
                if (received_value != expected_value) {
                    fprintf(stderr, "Error with data: expected - %u | received - %u \n", expected_value, received_value);
                    expected_value = received_value;
                }
                fprintf(stdout, "received : %u | expected : %u \n", received_value, expected_value);
                expected_value++;
            } else {
                perror("Read error");
                return EXIT_FAILURE;
            }
        }
        wait(NULL);

    }
    return EXIT_SUCCESS;
}
