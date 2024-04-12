#ifndef LAB_FILE_HANDLER_H
#define LAB_FILE_HANDLER_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdbool.h>

#define BUFFER_SIZE 1024
#define COPY_MORE 0644

bool file_handler_success(char *source, char *destination);

bool create_file_by_path(char *source, char *destination);

long get_file_size(FILE *f);

int do_stat(char *file_name);

bool reverse_copy_file_content(FILE *source, FILE *destination);


#endif //LAB_FILE_HANDLER_H
