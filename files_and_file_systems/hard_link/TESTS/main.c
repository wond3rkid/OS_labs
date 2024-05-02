#include <stdio.h>
#include "file_dir_handler.h"
#include "links_handler.h"

#define EXIT_FAILED 1
#define EXIT_SUCCESS 0

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Error with input, try again. \n");
        return EXIT_FAILED;
    }
    char cmd = *argv[1];
    char *input = argv[2];
    bool status;
    switch (cmd) {
        case 'a':
            status = mkdir_cmd(input);
            break;
        case 'b':
            status = ls_cmd(input);
            break;
        case 'c':
            status = rmdir_cmd(input);
            break;
        case 'd':
            status = touch_cmd(input);
            break;
        case 'e':
            status = cat_file(input);
            break;
        case 'f':
            status = rmfile_cmd(input);
            break;
        case 'g':
            status = create_symlink(input);
            break;
        case 'h':
            status = get_symlink(input) == NULL ? false : true;
            break;
        case 'i':
            status = get_file_symlink(input);
            break;
        case 'j':
            status = delete_symlink(input);
            break;
        case 'k':
            status = create_hardlink(input);
            break;
        case 'l' :
            status = delete_hardlink(input);
            break;
        case 'm':
            status = ls_la_cmd(input);
            break;
        case 'n':
            status = chmod_cmd(input);
            break;
        default:
            status = false;
            fprintf(stderr, "Error with input. The command %c doesn't exist.\n", cmd);
            return EXIT_FAILED;
    }
    return status == true ? EXIT_SUCCESS : EXIT_FAILED;
}