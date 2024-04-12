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

    strcat(temp_dest, "/\0");
    strcat(temp_src, "/\0");

    if (dir_ptr == NULL) {
        fprintf(stderr, "Cannot open directory %s for copying. \n", source);
        return false;
    }

    direntp = readdir(dir_ptr);

    while (direntp) {
        if (do_stat(direntp->d_name)) {
            char *rev_name = reverse_only_name(direntp->d_name);
            bool create = create_file_by_path_name(temp_src, direntp->d_name, temp_dest, rev_name);
            if (!create) {
                fprintf(stderr, "I am not okay with creating \n");
                return false;
            }
        }

        direntp = readdir(dir_ptr);
    }
    return true;
}

char *get_full_path(char *path, char *name) {
    long length = strlen(path) + strlen(name);
    char *full = malloc(sizeof(char) * length);
    int i = 0;
    while (i < strlen(path)) {
        full[i] = *(path + i);
        i++;
    }

    int j = 0;
    while (j < strlen(name)) {
        full[i] = *(name + j);
        i++;
        j++;
    }

    return full;
}

bool create_file_by_path_name(char *src_path, char *src_name, char *dest_path, char *dest_name) {
    char *source = get_full_path(src_path, src_name);
    char *destination = get_full_path(dest_path, dest_name);

    FILE *in_fd = fopen(source, "r");
    if (in_fd == NULL) {
        fprintf(stderr, "Error with opening source %s file : \n", source);
        return false;
    }

    FILE *out_fd = fopen(destination, "w");
    if (out_fd == NULL) {
        fprintf(stderr, "Error with creating the file: %s \n", destination);
        return false;
    }

    reverse_copy_file_content(in_fd, out_fd);

    if (fclose(in_fd) != 0) {
        fprintf(stderr, "Error with closing files %s. \n", source);
        return false;
    }
    if (fclose(out_fd) != 0) {
        fprintf(stderr, "Error with closing files %s. \n", destination);
        return false;
    }
    return true;
}


void reverse_copy_file_content(FILE *source, FILE *destination) {
    long source_size = get_file_size(source);
    fseek(source, -1, SEEK_END);
    long i = source_size;
    while (i > 0) {
        char current_char = fgetc(source);
        fprintf(destination, "%c", current_char);
        fseek(source, -2, SEEK_CUR);
        i--;
    }
}

long get_file_size(FILE *f) {
    fseek(f, 0, SEEK_END);
    long size = ftell(f);
    fseek(f, 0, SEEK_SET);
    return size;
}

int do_stat(char *file_name) {
    struct stat fileInfo;
    if (stat(file_name, &fileInfo) >= 0) {
        if (S_ISREG(fileInfo.st_mode)) {
            return 1;
        } else {
            return 0;
        }
    }
}
