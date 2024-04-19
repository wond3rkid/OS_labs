#include <assert.h>
#include "links_handler.h"

char *create_symlink(char *link) {
    char *new_link = malloc(strlen(link) + 1);
    assert(new_link != NULL);
    strcpy(new_link, link);
    if (access(new_link, F_OK) == 0) {
        perror("File already exists: ");
        free(new_link);
        return NULL;
    }
    if (symlink(link, new_link) == -1) {
        perror("Error with symlink");
        free(new_link);
        return NULL;
    }
    printf("Symbolic link to file %s created: %s\n", link, new_link);
    return new_link;
}

bool get_symlink(char *link) {
    char target_path[256];
    ssize_t num_bytes = readlink(link, target_path, sizeof(target_path) - 1);
    if (num_bytes == -1) {
        perror("Error with readlink");
        return false;
    }
    target_path[num_bytes] = '\0';
    printf("Content of symbolic link %s: %s\n", link, target_path);
    return true;
}

bool get_file_symlink(char *link) {
    return 0;
}

bool delete_symlink(char *link) {
    return 0;
}

bool create_hardlink(char *path) {
    return 0;
}

bool delete_hardlink(char *path) {
    return 0;
}
