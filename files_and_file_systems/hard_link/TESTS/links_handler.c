#include "links_handler.h"

char *create_symlink(char *link) {
    int path_hash = get_num();
    char *new_link = malloc(strlen(link) + 1);
    assert(new_link != NULL);
    snprintf(new_link, sizeof(link) + 1, "%s_%d", link, path_hash);
    if (symlink(link, new_link) == -1) {
        perror("Error with symlink. Terminated");
        free(new_link);
        return NULL;
    }
    printf("Symbolic link to file %s created: %s\n", link, new_link);
    return new_link;
}

char *get_symlink(char *link) {
    long path_max = pathconf(link, _PC_PATH_MAX);
    if (path_max == -1) {
        perror("Pathconf wasn't got");
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
        perror("Error with delete link");
        return false;
    }
    return true;
}

bool create_hardlink(char *path) {
    int path_hash = get_num();
    char *link_path = calloc(sizeof(char), strlen(path) + 1);
    assert(link_path != NULL);
    snprintf(link_path, sizeof(path) + 1, "%s_%d", path, path_hash);
    if (link(path, link_path) == -1) {
        perror("Hard link wasn't created");
        return false;
    }
    printf("Hard link created: %s -> %s\n", link_path, path);
    return true;
}

bool delete_hardlink(char *link) {
    int status = unlink(link);
    if (status != 0) {
        perror("Error with delete link");
        return false;
    }
    return true;
}

int get_num() {
    srand(time(NULL));
    return rand() % 10;
}