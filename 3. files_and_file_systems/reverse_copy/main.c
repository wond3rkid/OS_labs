#include <stdio.h>
#include <string.h>
#include "dir_handler.h"
#include "file_handler.h"

#define EXIT_SUCCESS 0
#define EXIT_FAIL 1

int main(int argc, char **argv) {
    if (argc != 2) {
        fprintf(stderr, "No arguments or too few arguments. Restart program and write the dir path.");
        return EXIT_FAIL;
    }
    char *path = argv[1];
    char *reversed_path = dir_handle_success(path);
    if (reversed_path == NULL) {
        return EXIT_FAIL;
    }
    printf("Directory was created. Start creating files. \n");
    bool files = file_handler_success(path, reversed_path);
    if (!files) {
        return EXIT_FAIL;
    }
    printf("Files were created. Program executed without problems.\n");
    return EXIT_SUCCESS;
}