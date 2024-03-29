#include <sys/stat.h>
#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <stdlib.h>
#include <dirent.h>
#include <stdbool.h>

#define EXIT_SUCCESS 0
#define EXIT_ERROR 1

void split_catalog_name_from_path(char *full_path, char *only_name, char *only_path, int path_length, int name_length) {
    strncpy(only_path, full_path, path_length);
    only_path[path_length] = '\0';
    strncpy(only_name, full_path + path_length, name_length);
    only_name[name_length] = '\0';
}

void get_lengths(int *name_length, int *path_length, const char *full) {
    *path_length = strlen(full);
    while (*(full + *path_length) != '/') {
        (*path_length)--;
    }
    (*path_length)++;
    *name_length = strlen(full) - *path_length;
}

void reverse_string(char *str, char *rev_str) {
    size_t length = strlen(str);
    char *end = str + length - 1;
    while (str <= end) {
        *rev_str = *end;
        end--;
        rev_str++;
    }
    rev_str[length] = '\0';
}

void get_full_path(const char *name, const char *path, char *res_path) {
    strcat(res_path, path);
    strcat(res_path, name);
}

void create_directory(char *name) {
    mkdir(name, 0700);
}

void file_name_handler(char *name, char *res_name) {
    size_t length = strlen(name);
    int ind = 0;
    while (ind != length) {
        if (name[ind] == '.') {
            //file .smth
        }
        ind++;
    }
    char *rev_name = malloc(sizeof(char) * ind);
    strncpy(rev_name, name, ind);
    reverse_string(rev_name, res_name);
    res_name[ind] = '\0';
}

bool file_reverse_write(FILE *file_src, FILE *file_dest) {
    if (file_dest == NULL || file_src == NULL) {
        perror("Error with open file");
        return EXIT_ERROR;
    }
    //rb wb
    fseek(file_src, 0, SEEK_END);
    long file_size = ftell(file_src);
    fseek(file_src, 0, SEEK_SET);
    char *buffer = (char *) malloc(file_size * sizeof(char));
    if (buffer == NULL) {
        perror("Memory allocating error");
        return EXIT_ERROR;
    }
    fread(buffer, sizeof(char), file_size, file_src);
    for (long i = file_size - 1; i >= 0; i--) {
        fwrite(&buffer[i], sizeof(char), 1, file_dest);
    }
    fclose(file_dest);
    free(buffer);

    printf("Successful copy.\n");
    return EXIT_SUCCESS;
}

void handle_file(FILE *src, char *src_name) {
    char *rev_name = malloc(sizeof(char) * (strlen(src_name)));
    file_name_handler(src_name, rev_name);

    FILE *dest= fopen(rev_name, "wb");
    file_reverse_write(src, dest);
    fclose(dest);
}

bool directory_handler(char *path, char *dstn_path) {
    DIR *d;
    struct dirent *dir;
    d = opendir(path);
    if (d == NULL) {
        fprintf(stderr, "Error with opening directory");
        return EXIT_ERROR;
    }
    while ((dir = readdir(d)) != NULL) {
        struct stat file_stat;
        if (stat(dir->d_name, &file_stat) == 0) {
            if (S_ISREG(file_stat.st_mode)) {
                FILE *src = fopen(dir->d_name, "rb");
                handle_file(src, dir->d_name);
                fclose(src);
            }
        } else {
            fprintf(stderr, "Error with getting info about this file: %s", dir->d_name);
            continue;
        }
    }
    closedir(d);
    return EXIT_SUCCESS;
}

int main(int argc, char *argv[]) {
    /*if (argc != 2) {
        fprintf(stderr, "You have to pass the directory path");
        return EXIT_ERROR;
    }
    char *full_catalog_path = argv[1];
    */
    char *full_catalog_path = "/home/freak1rget/CLionProjects/oslab3/cmake-build-debug/tmp";
    int name_length = 0, path_length = 0;
    get_lengths(&name_length, &path_length, full_catalog_path);
    char *catalog_name = malloc(sizeof(char) * name_length);
    char *path_to_catalog = malloc(sizeof(char) * path_length);
    split_catalog_name_from_path(full_catalog_path, catalog_name, path_to_catalog, path_length, name_length);
    char new_catalog_name; // имя каталога
    reverse_string(catalog_name, &new_catalog_name);

    char new_path[name_length + path_length + 1]; //весь путь дло каталога
    get_full_path(&new_catalog_name, path_to_catalog, (char *) &new_path);
    new_path[path_length + name_length + 1] = '\0';
    create_directory(new_path);
//  create_file("/home/freak1rget/CLionProjects/oslab3/cmake-build-debug/pmt/my.txt");
    directory_handler(full_catalog_path, new_path);
    free(catalog_name);
    free(path_to_catalog);

    return EXIT_SUCCESS;
}