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
    assert(rev_name != NULL);
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
    if (dir_ptr == NULL) {
        perror("Error with opening directory for copying: ");
        return false;
    }
    struct dirent *direntp;
    char temp_dest[strlen(destination) + 1];
    char temp_src[strlen(source) + 1];

    strcpy(temp_dest, destination);
    strcpy(temp_src, source);

    strcat(temp_dest, "/\0");
    strcat(temp_src, "/\0");

    direntp = readdir(dir_ptr);

    while (direntp) {
        if (do_stat(direntp->d_name)) {
            char *rev_name = reverse_only_name(direntp->d_name);
            bool create = create_file_by_path_name(temp_src, direntp->d_name, temp_dest, rev_name);
            if (!create) {
                perror("Error with creating reversed directory: ");
                return false;
            }
            free(rev_name);
        }

        direntp = readdir(dir_ptr);
    }
    if (closedir(dir_ptr) == -1){
        perror("Error with close");
        return false;
    }
    return true;
}

char *get_full_path(char *path, char *name) {
    unsigned long length = strlen(path) + strlen(name);
    char *full = malloc(sizeof(char) * length);
    assert(full != NULL);
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
        perror("Error with opening source file: ");
        return false;
    }

    FILE *out_fd = fopen(destination, "w");
    if (out_fd == NULL) {
        perror("Error with creating destination file: ");
        return false;
    }

    reverse_copy_file_content(in_fd, out_fd);
    free(source);
    free(destination);
    if (fclose(in_fd) != 0) {
        perror("Error with closing source file");
        return false;
    }
    if (fclose(out_fd) != 0) {
        perror("Error with closing destination file");
        return false;
    }

    return true;
}

void reverse_copy_file_content(FILE *source, FILE *destination) {
    long source_size = get_file_size(source);
    int fseek_flag = fseek(source, -1, SEEK_END);
    assert(fseek_flag == 0);
    long i = source_size;
    while (i > 0 && fseek_flag == 0) {
        char current_char = fgetc(source);
        fprintf(destination, "%c", current_char);
        fseek_flag = fseek(source, -2, SEEK_CUR);
        i--;
    }
}

long get_file_size(FILE *f) {
    int fseek_flag = fseek(f, 0, SEEK_END);
    assert(fseek_flag == 0);
    long size = ftell(f);
    fseek_flag = fseek(f, 0, SEEK_SET);
    assert(fseek_flag == 0);
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
    } else {
        perror("Stat");
        return 0;
    }
}
