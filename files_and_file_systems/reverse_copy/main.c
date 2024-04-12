#include <stdio.h>
#include <string.h>
#include "dir_handler.h"
#include "file_handler.h"

#define EXIT_SUCCESS 0
#define EXIT_FAIL 1

int main(int argc, char **argv) {
    if (argc != 2) {
        perror("Problem with input. Try again: ");
        return EXIT_FAIL;
    }
    char *path = argv[1];
    if (!check_exist(path)) {
        perror("Inputed directory doesn't exist: ");
        return EXIT_FAIL;
    }
    char *reversed_path = NULL;
    bool dir = dir_handle_success(path, &reversed_path);
    if (!dir) {
        perror("Error with copying of directory : ");
        return EXIT_FAIL;
    }
    printf("Directory was created. Start creating files. \n");
    bool files = file_handler_success(path, reversed_path);
    if (!files) {
        perror("Program executed with an error: ");
        return EXIT_FAIL;
    }
    printf("Files were created. Program executed without problems.\n");
    return EXIT_SUCCESS;
}