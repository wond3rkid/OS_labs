#include <stdio.h>
#include <string.h>
#include "dir_handler.h"
#include "file_handler.h"

#define EXIT_SUCCESS 0
#define EXIT_FAIL 1

int main(int argc, char **argv) {
    /*if (argc != 2) {
        fprintf(stderr, "An error with input. Try again!");
        return EXIT_FAIL;
    }
    char *path = argv[1];
    */

    char *test;
    test = "/home/freak1rget/CLionProjects/OS_labs/files_and_file_systems/reverse_copy/tmp";
    if (!check_exist(test)) {
        fprintf(stderr, "Input directory %s doesn't exist. \n", test);
        return EXIT_FAIL;
    }
    char *reversed_path = NULL;
    bool dir = dir_handle_success(test, &reversed_path);
    if (!dir) {
        fprintf(stderr, "Program executed with an error. Check console output before. Problem with directory copy. \n");
        return EXIT_FAIL;
    }
    fprintf(stderr, "Directory was created. Go to creating files: \n");
    bool files = file_handler_success(test, reversed_path);
    if (!files) {
        fprintf(stderr, "Program executed with an error. Check console output before. Problem with files copy. \n");
        return EXIT_FAIL;
    }
    return EXIT_SUCCESS;
}