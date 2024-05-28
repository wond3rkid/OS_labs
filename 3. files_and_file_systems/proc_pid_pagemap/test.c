#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    void *ptr = malloc(1024 * 1024 * 10);
    if (ptr == NULL) {
        perror("malloc");
        return 1;
    }

    memset(ptr, 0, 1024 * 1024 * 10);
    printf("PID: %d\n", getpid());
    sleep(60);
    free(ptr);
    return 0;
}
