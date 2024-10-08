#ifndef LAB_DIR_HANDLER_H
#define LAB_DIR_HANDLER_H

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <errno.h>
#include <dirent.h>
#include <stdbool.h>
#include <assert.h>

int create_reversed_dir(char *path);

char *get_reversed_path(const char *input_path, unsigned long path_length, unsigned long last_slash);

char *dir_handle_success(char *input_path);

bool check_exist(char *reversed_path);

#endif //LAB_DIR_HANDLER_H
