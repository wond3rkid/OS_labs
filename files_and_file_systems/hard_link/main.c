#include <stdio.h>
#include "file_dir_handler.h"
#include "links_handler.h"

#define EXIT_FAILED 1
#define EXIT_SUCCESS 0

int main() {
    printf("Print ? to see the list of supported commands. \n");
    char cmd = '\0';
    printf("Please print the command sym: \n");
    scanf("%c", &cmd);
    char *input = calloc(sizeof(char), 500);
    if (input == NULL) {
        printf("Error with memory allocation. \n");
        return EXIT_FAILED;
    }
    bool status;
    switch (cmd) {
        case '?':
            printf("List of supported commands: \na - mkdir \nb - ls\nc - rmdir \n");
            printf("d - touch \ne - cat \nf - rm file \ng - create symlink \nh - get symlink \ni - cat symlink file \nj - rm symlink \nk - create hardlink \n");
            printf("l - delete hardlink \nm - get info about file\nn - change rights\n");
            status = true;
            break;
        case 'a':
            printf("Write the path to the directory you want to create: \n");
            scanf("%s", input);
            printf("Your input: %s \n", input);
            status = mkdir_cmd(input);
            break;
        case 'b':
            printf("Write the path to the directory whose contents you want to view: \n");
            scanf("%s", input);
            printf("Your input: %s \n", input);
            status = ls_cmd(input);
            break;
        case 'c':
            printf("Write the path to the directory you want to delete: \n");
            scanf("%s", input);
            printf("Your input: %s \n", input);
            status = rmdir(input);
            break;
        case 'd':
            printf("Write the path to the file you want to create: \n");
            scanf("%s", input);
            printf("Your input: %s \n", input);
            status = touch_cmd(input);
            break;
        case 'e':
            printf("Write the path to the file whose contents you want to display: \n");
            scanf("%s", input);
            printf("Your input: %s \n", input);
            status = cat_file(input);
            break;
        case 'f':
            printf("Write the path to the file whose contents you want to delete: \n");
            scanf("%s", input);
            printf("Your input: %s \n", input);
            status = rmfile_cmd(input);
            break;
        case 'g':
            printf("Write the path to the file for which you want to create a symbolic link: \n");
            scanf("%s", input);
            printf("Your input: %s \n", input);
            status = create_symlink(input);
            break;
        case 'h':
            printf("Write a symbolic link where you want to get the content (where it points): \n");
            scanf("%s", input);
            printf("Your input: %s \n", input);
            status = get_symlink(input) == NULL ? false : true;
            break;
        case 'i':
            printf("Write a symbolic link where you want to get the contents of the file: \n");
            scanf("%s", input);
            printf("Your input: %s \n", input);
            status = get_file_symlink(input);
            break;
        case 'j':
            printf("Write the path to the file to which you want to remove the symbolic link: \n");
            scanf("%s", input);
            printf("Your input: %s \n", input);
            status = delete_symlink(input);
            break;
        case 'k':
            printf("Write the path to the file for which you want to create a hard link: \n");
            scanf("%s", input);
            printf("Your input: %s \n", input);
            status = create_hardlink(input);
            break;
        case 'l' :
            printf("Write the path to the file for which you want to delete a hard link: \n");
            scanf("%s", input);
            printf("Your input: %s \n", input);
            status = delete_hardlink(input);
            break;
        case 'm':
            printf("Write the path to the file for which you want to see the number of hard links and access rights: \n");
            scanf("%s", input);
            printf("Your input: %s \n", input);
            status = ls_la_cmd(input);
            break;
        case 'n':
            printf("write the path to the file for which you want to change access rights: \n");
            scanf("%s", input);
            printf("Your input: %s \n", input);
            status = chmod_cmd(input);
            break;
        default:
            status = false;
            fprintf(stderr,
                    "Error with input. The command %c doesn't exist. You can check all exist command by writing '?'. \n",
                    cmd);
            return EXIT_FAILED;
    }
    return status == true ? EXIT_SUCCESS : EXIT_FAILED;
}