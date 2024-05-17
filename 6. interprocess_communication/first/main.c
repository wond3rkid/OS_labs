#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <unistd.h>
#include <stdbool.h>
#include <sys/wait.h>

#define PAGE_SIZE sysconf(_SC_PAGESIZE)
#define PAGE_CONST (PAGE_SIZE / sizeof(unsigned int))

int main() {
    size_t region_size = PAGE_SIZE;
    unsigned int *shared_region = mmap(NULL, region_size, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    if (shared_region == NULL) {
        perror("Allocate memory error");
        return EXIT_FAILURE;
    }
    pid_t child = fork();
    if (child == -1) {
        perror("Fork error");
        return EXIT_FAILURE;
    } else if (child == 0) {
        unsigned int tmp = 0;
        while (true) {
            shared_region[tmp % PAGE_CONST] = tmp;
            tmp++;
        }
    } else {
        unsigned int value = 0;
        while (true) {
            for (unsigned int i = 0; i < PAGE_CONST; i++) {
                if (shared_region[i] != value) {
                    fprintf(stderr, "Error with data: expected - %u | received - %u \n", value, shared_region[i] );
                    value = shared_region[i];
                }
                value++;
            }
        }
        wait(NULL);
    }
    return 0;
}