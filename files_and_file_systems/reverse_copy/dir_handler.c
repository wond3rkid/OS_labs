#include <string.h>
#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <errno.h>
#include "dir_handler.h"

bool create_reversed_dir(char *path) {

}

char *get_reversed_path(const char *input_path, unsigned long path_length, unsigned long last_slash) {
    char *reversed_dir_name = malloc(sizeof(char) * (path_length - last_slash + 1));
    int j = 0;
    for (int i = path_length - 1; i > last_slash; i--) {
        fprintf(stderr, "input path [%d] = %c \n", i, input_path[i]);
        reversed_dir_name[j] = *(input_path + i);
        j += 1;
    }
    fprintf(stderr, "check reversed dir name: %s \n", reversed_dir_name);
    char *reversed_path = malloc(sizeof(char) * path_length);
    j = 0;
    while (j <= last_slash) {

        reversed_path[j] = *(input_path + j);
        fprintf(stderr, "current j : %d current char : %c", j, reversed_path[j]);
        j += 1;
    }
    int i = 0;
    while (i < strlen(reversed_dir_name)) {
        reversed_path[j] = *(reversed_dir_name + i);
        fprintf(stderr, "current rev_path[%d] : %c\n", j, reversed_path[j]);
        i += 1;
        j += 1;
    }
    fprintf(stderr, "current reversed path : %s \n", reversed_path);
    if (strlen(reversed_path) != path_length) {
        fprintf(stderr, "Here is an error: reversed path wasn't created. \n");
        exit(1);
    }
    return reversed_path;
}

bool dir_handle_success(char *input_path, char *reversed_path) {
    unsigned long last_slash = strlen(input_path);
    const unsigned long path_length = strlen(input_path);
    fprintf(stderr, "input path length: %lu \n", path_length);
    while (*(input_path + last_slash) != '/') {
        last_slash--;
    }
    fprintf(stderr, "current last_slash = %lu \n", last_slash);
    reversed_path = get_reversed_path(input_path, path_length, last_slash);
    fprintf(stderr, "current_reversed full path after func: %s; it's length: %lu \n", reversed_path,
            strlen(reversed_path));
    struct stat st = {0};
    bool mkdir_flag = mkdir(reversed_path, 0700);
    if (mkdir_flag != 0) {
        fprintf(stderr, "Directory wasn't created: Here is the reason: %s \n", errno);
        return false;
    }
    fprintf(stderr, "Directory by the path %s was created successfully! \n", reversed_path);
    return true;
}