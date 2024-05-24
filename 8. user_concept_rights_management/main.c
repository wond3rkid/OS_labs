#include <stdio.h>
#include <unistd.h>
#include <pwd.h>

void print_ids() {
    uid_t real_uid = getuid();
    uid_t effective_uid = geteuid();
    struct passwd *pw = getpwuid(real_uid);
    struct passwd *pw_eff = getpwuid(effective_uid);
    printf("Real UID: %d (%s)\n", real_uid, pw->pw_name);
    printf("Effective UID: %d (%s)\n", effective_uid, pw_eff->pw_name);
}

void read_file(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening file");
        return;
    }
    char ch;
    while ((ch = fgetc(file)) != EOF) {
        putchar(ch);
    }
    fclose(file);
}

int main() {
    const char *filename = "secret_file.txt";
    printf("Contents of the file:\n");
    read_file(filename);
    printf("\nUser IDs:\n");
    print_ids();
    return 0;
}
