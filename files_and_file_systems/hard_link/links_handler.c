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

char *get_symlink(char *link) {
    long path_max = pathconf(link, _PC_PATH_MAX);
    if (path_max == -1) {
        perror("Error getting pathconf");
        return NULL;
    }
    char *target_path = malloc(path_max + 1);
    assert(target_path != NULL);
    ssize_t num_bytes = readlink(link, target_path, path_max);
    if (num_bytes == -1) {
        perror("Error with readlink");
        return NULL;
    }
    target_path[num_bytes] = '\0';
    printf("Content of symbolic link %s: %s\n", link, target_path);
    return target_path;
}

bool get_file_symlink(char *link) {
    char *file_link = get_symlink(link);
    return cat_file(file_link);
}

bool delete_symlink(char *link) {
    int status = unlink(link);
    if (status != 0) {
        perror("Error with delete link: ");
        return false;
    }
    return true;
}

bool create_hardlink(char *path) {
    unsigned int path_hash = hash(path);
    char link_path[100];
    snprintf(link_path, sizeof(link_path), "hardlink_%u", path_hash);

    if (link(path, link_path) == -1) {
        perror("Error creating hard link");
        return false;
    }
    printf("Hard link created: %s -> %s\n", link_path, path);
    return true;
}

bool delete_hardlink(char *link) {
    int status = unlink(link);
    if (status != 0) {
        perror("Error with delete link: ");
        return false;
    }
    return true;
}

unsigned int hash(const char *str) {
    unsigned int hash_value = 0;
    while (*str) {
        hash_value += *str;
        str++;
    }
    return hash_value % 11;
}