/*
 * на вход программе подается путь к каталогу
 * с помощью функции переворота строки, получаем имя нового каталога
 * создаем каталог с именем из п.2
 * смотрим названия файлов из исходного каталога, создаем новые файлы с перевернутыми именами и сразу заполняем их прежним содержимым
 * повторяем п.4 для всех файлов в исходной директории
*/
#include <sys/stat.h>
#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <stdlib.h>

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

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "You have to pass the directory path");
        return EXIT_ERROR;
    }
    
    char *full_catalog_path = "/home/freak1rget/CLionProjects/oslab3/cmake-build-debug/tmp";
    int name_length = 0, path_length = 0;
    get_lengths(&name_length, &path_length, full_catalog_path);
    char *catalog_name = malloc(sizeof(char) * name_length);

    char *path_to_catalog = malloc(sizeof(char) * path_length);
    split_catalog_name_from_path(full_catalog_path, catalog_name, path_to_catalog, path_length, name_length);
    char new_catalog_name;

    reverse_string(catalog_name, &new_catalog_name);

    char new_path[name_length + path_length + 1];

    get_full_path(&new_catalog_name, path_to_catalog, &new_path);

    new_path[path_length + name_length + 1] = '\0';

    fprintf(stderr, "3. %s \n", new_path);

    create_directory(new_path);
    free(catalog_name);
    free(path_to_catalog);
    return EXIT_SUCCESS;
}
