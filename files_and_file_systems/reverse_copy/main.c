#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include "dir_handler.h"
#include "file_handler.h"

#define EXIT_SUCCESS 0
#define EXIT_FAIL 1

int main(int argc, char **argv) {
    if (argc != 2) {
        fprintf(stderr, "An error with input. Try again!");
        return EXIT_FAIL;
    }
    char *path = argv[1];
    char *test;
    test = "/home/freak1rget/CLionProjects/OS_labs/files_and_file_systems/reverse_copy/tmp";
    //test = "/m.m/mmmmm/oneoneone_\0";
    fprintf(stderr, "curr len of test: %lu \n", strlen(test));
    char *reversed_path = NULL;
    dir_handle_success(test, &reversed_path);
    fprintf(stderr, "now i am having this path: %s with this length: %lu \n", reversed_path, strlen(reversed_path));
}