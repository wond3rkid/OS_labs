#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

#define EXIT_SUCCESS 0
#define EXIT_FAILURE 1

void pagemap_reader() {

}

int main(int argc, char **argv) {
    if (argc != 2) {
        fprintf(stderr, "Invalid arguments count");
        return EXIT_FAILURE;
    }
    int pid;
    if (strcmp(argv[1], "self") == 0) {
        pid = getpid();
        printf("%d\n", pid);
    } else if (atoi(argv[1]) < 0) {
        fprintf(stderr, "Invalid pid, cannot be less than zero");
        return EXIT_FAILURE;
    } else {
        pid = atoi(argv[1]);
        printf("%d\n", pid);
    }


    return EXIT_SUCCESS;
}