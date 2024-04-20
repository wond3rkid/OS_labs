#include "dir_handler.h"

int create_reversed_dir(char *path) {
    if (check_exist(path)) {
        perror("The directory by inputed path already exists. Terminate program : ");
        return -1;
    }
    return mkdir(path, 0700);
}

char *get_reversed_path(const char *input_path, unsigned long path_length, unsigned long last_slash) {
    char *reversed_dir_name = malloc(sizeof(char) * (path_length - last_slash + 1));
    assert(reversed_dir_name != NULL);
    size_t j = 0;
    for (size_t i = path_length - 1; i > last_slash; i--) {
        reversed_dir_name[j] = *(input_path + i);
        j += 1;
    }
    char *reversed_path = malloc(sizeof(char) * path_length);
    assert(reversed_path != NULL);
    j = 0;
    while (j <= last_slash) {
        reversed_path[j] = *(input_path + j);
        j += 1;
    }
    size_t i = 0;
    while (i < strlen(reversed_dir_name)) {
        reversed_path[j] = *(reversed_dir_name + i);
        i += 1;
        j += 1;
    }
    if (strlen(reversed_path) != path_length) {
        perror("Reversed path wasn't created: ");
        exit(1);
    }
    free(reversed_dir_name);
    return reversed_path;
}

bool dir_handle_success(char *input_path, char **reversed_path) {
    unsigned long last_slash = strlen(input_path);
    const unsigned long path_length = strlen(input_path);
    while (*(input_path + last_slash) != '/') {
        last_slash--;
    }
    char *reversed_path_ptr = get_reversed_path(input_path, path_length, last_slash);
    *reversed_path = reversed_path_ptr;
    int mkdir_flag = create_reversed_dir(*reversed_path);
    free(reversed_path_ptr);
    if (mkdir_flag != 0) {
        perror("Directory wasn't created: ");
        return false;
    } else {
        printf("Directory by the path %s was created successfully! \n", *reversed_path);
        return true;
    }
}

bool check_exist(char *reversed_path) {
    DIR *dir = opendir(reversed_path);
    if (dir) {
        closedir(dir);
        return true;
    }
    perror("Dir wasn't opened");
    return false;
}
