#ifndef LAB_FILE_HANDLER_H
#define LAB_FILE_HANDLER_H
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdbool.h>

bool file_handler_success(char *source, char *destination);

bool create_file_by_path_name(char *src_path, char *src_name, char *dest_path, char *dest_name);

char *get_full_path(char *path, char *name);

long get_file_size(FILE *f);

int do_stat(char *file_name);

void reverse_copy_file_content(FILE *source, FILE *destination);

#endif //LAB_FILE_HANDLER_H
