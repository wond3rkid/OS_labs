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
    //test = "/home/freak1rget/CLionProjects/OS_labs/files_and_file_systems/reverse_copy/tmp";
    //test = "/m.m/mmmmm/oneoneone_\0";
    fprintf(stderr, "curr len of test: %lu \n", strlen(test));
    dir_handle_success(test, test);

}