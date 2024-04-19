#include <stdio.h>
#include "file_dir_handler.h"
#define btoa(x) ((x)?"true":"false")
#define EXIT_FAILED 1
#define EXIT_SUCCESS 0

int main(int argc, char **argv) {
    printf("List of supported commands: \na - mkdir \nb - ls\nc - rmdir \n");
    printf("d - touch \ne - cat \nf - rm file \ng - create symlink \nh - get symlink \ni - cat symlink file \nj - rm symlink \nk - create hardlink \n");
    printf("l - delete hardlink \nm - get info about file\nn - change rights\n");
    printf("You have to input your command and argument! \n\n");
//    if (argc != 3) {
//        perror("Problem with input. Try again");
//        return EXIT_FAILED;
//    }
//    switch (char cmd) {
//        case :
//    }
    char *test_path = "/home/freak1rget/CLionProjects/OS_labs/files_and_file_systems/hard_link/main.c";
    printf("\n %s \n", btoa(chmod_cmd(test_path)));
    return EXIT_SUCCESS;
}