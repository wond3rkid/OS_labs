#include <stdio.h>

#define EXIT_FAILED 1
#define EXIT_SUCCESS 0

int main(int argc, char **argv) {
    printf("List of supported commands: \na - mkdir \nb - ls\nc - rmdir \n");
    printf("d - touch \ne - cat \nf - rm file \ng - create symlink \nh - get symlink \ni - cat symlink file \nj - rm symlink \nk - create hardlink \n");
    printf("l - delete hardlink \nm - get info about file\nn - change rights\n");
    printf("You have to input your command and argument!");
    if (argc != 3) {
        perror("Problem with input. Try again");
        return EXIT_FAILED;
    }
    return EXIT_SUCCESS;
}