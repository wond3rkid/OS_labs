#ifndef HARD_LINK_LINKS_HANDLER_H
#define HARD_LINK_LINKS_HANDLER_H

#include <dirent.h>
#include <string.h>
#include <malloc.h>
#include <unistd.h>
#include <stdbool.h>
#include <sys/stat.h>
#include <stdio.h>

char *create_symlink(char *link);

bool get_symlink(char *link);

bool get_file_symlink(char *link);

bool delete_symlink(char *link);

bool create_hardlink(char *path);

bool delete_hardlink(char *path);

#endif //HARD_LINK_LINKS_HANDLER_H
