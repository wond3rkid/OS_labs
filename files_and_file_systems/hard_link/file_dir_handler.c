#include <fcntl.h>
#include "file_dir_handler.h"

#define BUFFER_SIZE 1024

bool mkdir_cmd(char *path) {
    printf("Creating directory by name : %s. \n", path);
    if (check_dir_exist(path)) {
        perror("Try to create another dir.\n");
        return false;
    }
    int status = mkdir(path, 0700);
    printf("Status of creating directory: %d", status);
    return status == -1 ? 1 : 0;
}


bool check_dir_exist(char *path) {
    printf("Trying to check if directory already exist: \n");
    DIR *dir = opendir(path);
    if (dir) {
        printf("Directory already exists. ");
        int status = closedir(dir);
        printf("Status of closing dir : %d.\n", status);
        return status == 0 ? true : false;
    }
    printf("Directory didn't exist.\n");
    return false;
}


bool ls_cmd(char *path) {
    printf("Getting the list of files from path: \n");
    DIR *d;
    struct dirent *dir;
    d = opendir(path);
    if (d) {
        while ((dir = readdir(d)) != NULL) {
            printf("%s\n", dir->d_name);
        }
        closedir(d);
    } else {
        perror("Directory by path %s wasn't opened");
        return false;
    }
    return true;
}


bool rmdir_cmd(char *path) {
    printf("Trying to delete dir by path: %s \n", path);
    size_t path_length;
    char *full_path;
    DIR *dir;
    struct stat stat_path, stat_entry;
    struct dirent *entry = NULL;
    stat(path, &stat_path);

    if (S_ISDIR(stat_path.st_mode) == 0) {
        perror("This path is not dir. \n");
        return false;
    }
    if ((dir = opendir(path)) == NULL) {
        perror("Directory couldn't be opened.");
        return false;
    }

    path_length = strlen(path);

    while ((entry = readdir(dir)) != NULL) {
        if (!strcmp(entry->d_name, ".") || !strcmp(entry->d_name, "..")) {
            continue;
        }
        full_path = calloc(path_length + 1 + strlen(entry->d_name) + 1, sizeof(char));
        strcpy(full_path, path);
        strcat(full_path, "/");
        strcat(full_path, entry->d_name);
        stat(full_path, &stat_entry);
        fprintf(stderr, "current full path %s", full_path);
        if (S_ISDIR(stat_entry.st_mode) != 0) {
            rmdir_cmd(full_path);
            free(full_path);
            continue;
        }

        if (unlink(full_path) == 0) {
            printf("The file %s was removed.\n", full_path);
        } else {
            printf("Current file: %s \n", full_path);
            perror("The file was not removed;\n");
            return false;
        }
        free(full_path);
    }
    int rm = rmdir(path);
    if (rm != 0) {
        perror("Directory wasn't deleted.\n");
    } else {
        printf("Directory %s was deleted successfully! \n", path);
    }
    int close = closedir(path);
    return (rm + close) == 0 ? true : false;
}

bool check_file_exist(char *path) {
    if (access(path, F_OK) == 0) {
        perror("File is already exist");
        return true;
    }
    return false;
}

bool touch_cmd(char *path) {
    FILE *file = NULL;
    if (check_file_exist(path)) {
        perror("File is already exist");
        return false;
    }
    file = fopen(path, "a");
    if (file == NULL) {
        perror("File wasn't created");
        return false;
    }
    fclose(file);
    return true;
}

bool cat_file(char *path) {
    int file = open(path, O_RDONLY);
    if (file == -1) {
        perror("Cannot open file");
        return false;
    }
    char buffer[BUFFER_SIZE];
    int read_size;
    printf("Start cat the file %s: \n\n", path);
    while ((read_size = read(file, buffer, BUFFER_SIZE)) > 0) {
        write(1, &buffer, read_size);
    }
    int status = close(file);
    if (status != 0) {
        perror("Error with close file");
        return false;
    }
    return true;

}

bool rmfile_cmd(char *path) {
    if (!check_file_exist(path)) {
        perror("File doesn't exist");
        return false;
    }
    int status = remove(path);
    if (status == 0) {
        return true;
    }
    return false;
}