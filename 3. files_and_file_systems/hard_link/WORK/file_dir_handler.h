#ifndef HARD_LINK_FILE_DIR_HANDLER_H
#define HARD_LINK_FILE_DIR_HANDLER_H

#include <assert.h>
#include <dirent.h>
#include <string.h>
#include <malloc.h>
#include <unistd.h>
#include <stdbool.h>
#include <sys/stat.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>

#define BUFFER_SIZE 1024

bool mkdir_cmd(char *path);

bool check_dir_exist(char *path);

bool ls_cmd(char *path);

bool rmdir_cmd(char *path);

bool touch_cmd(char *path);

bool cat_file(char *path);

bool check_file_exist(char *path);

bool rmfile_cmd(char *path);

bool ls_la_cmd(char *path);

bool chmod_cmd(char *path);

#endif //HARD_LINK_FILE_DIR_HANDLER_H
