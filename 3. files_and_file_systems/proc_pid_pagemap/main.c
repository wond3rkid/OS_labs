#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdint.h>
#include <sys/types.h>
#include <sys/stat.h>

#define PAGE_SIZE 4096

void print_pagemap_entry(uint64_t entry) {
    if (entry & (1ULL << 63)) {
        printf("PFN: 0x%llx ", entry & ((1ULL << 55) - 1));
        if (entry & (1ULL << 62)) printf("swap ");
        if (entry & (1ULL << 61)) printf("file ");
    } else {
        printf("Page not present ");
    }
    printf("\n");
}

void read_pagemap(pid_t pid, unsigned long start, unsigned long end) {
    char pagemap_path[256];
    snprintf(pagemap_path, sizeof(pagemap_path), "/proc/%d/pagemap", pid);

    int pagemap_fd = open(pagemap_path, O_RDONLY);
    if (pagemap_fd == -1) {
        perror("Failed to open pagemap");
        exit(EXIT_FAILURE);
    }

    uint64_t entry;
    for (unsigned long vaddr = start; vaddr < end; vaddr += PAGE_SIZE) {
        off_t offset = (vaddr / PAGE_SIZE) * sizeof(entry);
        if (lseek(pagemap_fd, offset, SEEK_SET) == (off_t)-1) {
            perror("Failed to seek pagemap");
            close(pagemap_fd);
            exit(EXIT_FAILURE);
        }

        if (read(pagemap_fd, &entry, sizeof(entry)) != sizeof(entry)) {
            perror("Failed to read pagemap entry");
            close(pagemap_fd);
            exit(EXIT_FAILURE);
        }

        printf("Page %lx: 0x%016llx ", vaddr / PAGE_SIZE, (unsigned long long)entry);
        print_pagemap_entry(entry);
    }

    close(pagemap_fd);
}

void print_pagemap(pid_t pid) {
    char maps_path[256];
    snprintf(maps_path, sizeof(maps_path), "/proc/%d/maps", pid);

    FILE *maps_file = fopen(maps_path, "r");
    if (!maps_file) {
        perror("Failed to open maps file");
        exit(EXIT_FAILURE);
    }

    unsigned long start, end;
    char line[256];
    while (fgets(line, sizeof(line), maps_file)) {
        if (sscanf(line, "%lx-%lx", &start, &end) == 2) {
            read_pagemap(pid, start, end);
        }
    }

    fclose(maps_file);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <pid>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    pid_t pid = atoi(argv[1]);
    print_pagemap(pid);

    return 0;
}
