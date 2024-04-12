#ifndef LAB_DIR_HANDLER_H
#define LAB_DIR_HANDLER_H

#include "stdbool.h"

bool create_dir(char *path);

char *get_reversed_path(const char *input_path, unsigned long path_length, unsigned long last_slash);

bool dir_handle_success(char *input_path, char **reversed_path);

bool check_exist(char *reversed_path);

#endif //LAB_DIR_HANDLER_H
