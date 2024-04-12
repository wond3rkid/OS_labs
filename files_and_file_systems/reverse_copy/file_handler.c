#include "file_handler.h"

int dot_in_name(char *file_name) {
    int i = 0;
    while (i < strlen(file_name)) {
        if (file_name[i] == '.') {
            return i;
        }
        i++;
    }
    return -1;
}

char *reverse_only_name(char *file_name) {
    unsigned long file_length = strlen(file_name);
    char *rev_name = malloc(sizeof(char) * file_length);
    int i;
    int dot = dot_in_name(file_name);
    if (dot == -1) {
        i = 0;
        while (i <= file_length) {
            rev_name[i] = *(file_name + file_length - 1 - i);
            i++;
        }
    } else {
        i = dot - 1;
        while (i >= 0) {
            rev_name[dot - i - 1] = *(file_name + i);
            i--;
        }
        while (dot < file_length) {
            rev_name[dot] = *(file_name + dot);
            dot++;
        }
    }
    return rev_name;
}

bool file_handler_success(char *source, char *destination) {
    DIR *dir_ptr = opendir(source);
    struct dirent *direntp;

    char temp_dest[strlen(destination) + 1];
    char temp_src[strlen(source) + 1];

    strcpy(temp_dest, destination);
    strcpy(temp_src, source);

    strcat(temp_dest, "/");
    strcat(temp_src, "/");

    if (dir_ptr == NULL) {
        fprintf(stderr, "Cannot open directory %s for copying. \n", source);
        return false;
    }
    direntp = readdir(dir_ptr);
    while (direntp) {
        if (do_stat(direntp->d_name) == 1) {
            char *rev_name = reverse_only_name(direntp->d_name);
            strcat(temp_dest, rev_name);
            strcat(temp_src, direntp->d_name);
            bool file_created = create_file_by_path(temp_src, temp_dest);
            free(rev_name);
            if (!file_created) {
                fprintf(stderr, "Error with creating or filling the file. Check logs");
                return false;
            }
        }
        direntp = readdir(dir_ptr);
    }
    return true;
}

bool create_file_by_path(char *source, char *destination) {
    FILE *in_fd = fopen(source, "r");
    FILE *out_fd = fopen(destination, "w");
    char buf[BUFFER_SIZE];

    if (in_fd == NULL) {
        fprintf(stderr, "Error with opening source %s file: \n", source);
        return false;
    }

    if (out_fd == NULL) {
        fprintf(stderr, "Error with creating the file: %s \n", destination);
        return false;
    }

    bool rev_write = reverse_copy_file_content(in_fd, out_fd);
    if (!rev_write) {
        fprintf(stderr, "Error with writing from %s to %s. \n", source, destination);
        return false;
    }

    if (!fclose(in_fd) || !fclose(out_fd)) {
        fprintf(stderr, "Error with closing files %s and %s. \n", source, destination);
        return false;
    }
    return true;
}


bool reverse_copy_file_content(FILE *source, FILE *destination) {
    long source_size = get_file_size(source);
    fseek(source, -1, SEEK_END);
    long i = source_size;
    while (i > 0) {
        char current_char = fgetc(source);
        fprintf(destination, "%c", current_char);
        fseek(source, -2, SEEK_CUR);
        i--;
    }
    return true;
}

long get_file_size(FILE *f) {
    fseek(f, 0, SEEK_END); // seek to end of file
    long size = ftell(f); // get current file pointer
    fseek(f, 0, SEEK_SET); // seek back to beginning of file
    return size;
}

int do_stat(char *file_name) {
    struct stat fileInfo;
    if (stat(file_name, &fileInfo) >= 0) {
        if (S_ISREG(fileInfo.st_mode))
            return 1;
        else {
            return 0;
        }
    }
}