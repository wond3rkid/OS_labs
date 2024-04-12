#include <sys/stat.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <dirent.h>
#include <stdbool.h>
#include <fcntl.h>
#include <unistd.h>

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
    bool flag = false;
    int ind = 0;
    while (ind != length) {
        if (name[ind] == '.') {
            flag = true;
            break;
        }
        ind++;
    }
    // rev_name сейчас содержит строку до точки если точки нет то всю
    char *rev_name = malloc(sizeof(char) * ind);
    strncpy(rev_name, name, ind);
    rev_name[ind] = '\0';
    if (!flag) {
        reverse_string(rev_name, res_name);
        res_name[ind] = '\0';
    } else {
        char *tmp = malloc(sizeof(char) * ind);
        reverse_string(rev_name, tmp);
        strcat(res_name, rev_name);
        strcat(res_name, tmp + ind + 1);
        free(tmp);
    }
    free(rev_name);
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

void handle_file(FILE *src, char *src_name, char *dest_path) {
    // сначала переворачиваем имчя файла
    char *rev_name = malloc(sizeof(char) * (strlen(src_name)));

    char *full = malloc(sizeof(char) * (strlen(dest_path) + strlen(rev_name)));
    file_name_handler(src_name, rev_name);
    get_full_path(rev_name, dest_path, full);
    FILE *dest = fopen(rev_name, "wb");
    file_reverse_write(src, dest);
    fclose(dest);
}

bool directory_handler(char *path, char *dest_path) {
    fprintf(stderr, "%s \n", path);
    //обработчик открытия директории
    DIR *d;
    struct dirent *dir;
    d = opendir(path);

    if (d == NULL) {
        fprintf(stderr, "Error with opening directory");
        return EXIT_ERROR;
    }

    while ((dir = readdir(d)) != NULL) {
        struct stat file_stat;
        // если файл регулярный, то вызываем его обработчик, передавая туда, название файла, исходный файл, и директорию куда записываем этот файл потом файл закрываем
        fprintf(stderr, "current file %s isreg: %d file stat: %d  \n", dir->d_name, S_ISREG(file_stat.st_mode),
                stat(dir->d_name, &file_stat));

        if (stat(dir->d_name, &file_stat) == 0) {
            if (S_ISREG(file_stat.st_mode)) {
                FILE *src = fopen(dir->d_name, "rb");
                handle_file(src, dir->d_name, dest_path);
                fclose(src);
            }
        } else {
            fprintf(stderr, "Error with getting info about this file: %s \n", dir->d_name);
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

    // тут мы создали директорию уже с правильным именем перевернутую. в нью паф лежит путь до этой новой директории. ПЛЯШЕМ ОТ НЕЁ
    create_directory(new_path);
    // мы передаем тут путь  в исходный каталог и в новый, куда будем копировать
    directory_handler(full_catalog_path, new_path);

    FILE *test = fopen("/home/freak1rget/CLionProjects/oslab3/cmake-build-debug/tmp/my.txt", "r");
    if (test != NULL) {
        printf("ERRROR");
    }
    free(catalog_name);
    free(path_to_catalog);
    return EXIT_SUCCESS;
}