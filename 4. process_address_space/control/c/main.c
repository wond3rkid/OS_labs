#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <unistd.h>
#include <signal.h>
#include <stdbool.h>
#include <limits.h>

#define PAGE_SIZE sysconf(_SC_PAGESIZE)

void handle_sigsegv() {
    write(0, "Received SIGSEGV signal.", 24);
    exit(1);
}

void resursive_stack_array() {
    char array[4096];
    printf("Array pointer : %p \n", (void *) &array);
    sleep(1);
    resursive_stack_array();
}

_Noreturn void heap_array_while() {
    while (true) {
        char *array = malloc(INT_MAX);
        printf("Array pointer : %p \n", (void *) &array);
        sleep(1);
        free(array);
    }
}

void create_add() {
    size_t region_size = 10 * PAGE_SIZE;
    printf("Create new region address. \n");
    void *region_addr = mmap(NULL, region_size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    if (region_addr == MAP_FAILED) {
        perror("mmap");
        exit(1);
    }
    printf("Mapped a region at address %p with size %zu bytes. \n", region_addr, region_size);
    sleep(10);
    printf("Unmapping region. \n");
    if (munmap(region_addr, region_size) == -1) {
        perror("munmap");
        exit(1);
    }
}

void create_add_change() {
    size_t region_size = 10 * PAGE_SIZE;
    void *region_addr = mmap(NULL, region_size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    if (region_addr == MAP_FAILED) {
        perror("mmap");
        exit(1);
    }
    printf("Mapped a region at address %p with size %zu bytes\n", region_addr, region_size);

    char *message = "Hello world, i love doing os!";
    printf("Write to region: %s\n", message);
    sprintf(region_addr, "%s", message);
    printf("Read from region: %s\n", (char *) region_addr);
    printf("Change mprotect. \n");
    if (mprotect(region_addr, region_size, PROT_WRITE) == -1) {
        perror("mprotect");
        exit(1);
    }
    printf("Trying to read from region after mprotect(PROT_WRITE):\n");
    printf("%s\n", (char *) region_addr);

    if (mprotect(region_addr, region_size, PROT_READ) == -1) {
        perror("mprotect");
        exit(1);
    }

    printf("Trying to write to region after mprotect(PROT_READ):\n");
    sprintf(region_addr, "%s", message);
    // sigsegv here
    if (munmap(region_addr, region_size) == -1) {
        perror("munmap");
        exit(EXIT_FAILURE);
    }
}

void create_add_change_handled() {
    size_t region_size = 10 * PAGE_SIZE;
    void *region_addr = mmap(NULL, region_size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    if (region_addr == MAP_FAILED) {
        perror("mmap");
        exit(1);
    }
    printf("Mapped a region at address %p with size %zu bytes\n", region_addr, region_size);

    char *message = "Hello world, i love doing os!";
    printf("Write to region: %s\n", message);
    sprintf(region_addr, "%s", message);
    printf("Read from region: %s\n", (char *) region_addr);

    printf("Change mprotect. \n");
    if (mprotect(region_addr, region_size, PROT_WRITE) == -1) {
        perror("mprotect");
        exit(1);
    }
    signal(SIGSEGV, handle_sigsegv);

    printf("Trying to read from region after mprotect(PROT_WRITE):\n");
    printf("%s\n", (char *) region_addr);

    if (mprotect(region_addr, region_size, PROT_READ) == -1) {
        perror("mprotect");
        exit(1);
    }

    printf("Trying to write to region after mprotect(PROT_READ):\n");
    sprintf(region_addr, "%s", message);
    // sigsegv here
    if (munmap(region_addr, region_size) == -1) {
        perror("munmap");
        exit(EXIT_FAILURE);
    }
}

void create_add_part() {
    size_t region_size = 10 * PAGE_SIZE;
    printf("Create new region address. \n");
    void *region_addr = mmap(NULL, region_size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    if (region_addr == MAP_FAILED) {
        perror("mmap");
        exit(1);
    }
    printf("Mapped a region at address %p with size %zu bytes. \n", region_addr, region_size);
    sleep(10);

    size_t partial_size = 3 * PAGE_SIZE;
    void *partial_addr = region_addr + 3 * PAGE_SIZE;
    printf("Unmapping a part of the region at addr %p with size %zu bytes. \n", partial_addr, partial_size);
    if (munmap(partial_addr, partial_size) == -1) {
        perror("munmap");
        exit(1);
    }
    sleep(10);

    printf("Unmapping the remaining part of the region. \n");
    if (munmap(region_addr, region_size) == -1) {
        perror("munmap");
        exit(1);
    }
    sleep(10);
}

int main() {
    printf("My pid: %d \n", getpid());
    sleep(2);
//    resursive_stack_array();
//    heap_array_while();
//    create_add();
//    create_add_change();
    create_add_change_handled();
//    create_add_part();
    return 0;
}