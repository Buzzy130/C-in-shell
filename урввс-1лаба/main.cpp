#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

void list_directories(const char* path) {
    printf("%s\n", path);
    printf("Directories in the current directory:\n");
    struct dirent* entry;
    DIR* dir = opendir(path);
    if (dir == NULL) {
        perror("opendir");
        exit(1);
    }
    while ((entry = readdir(dir))) {
        if (entry->d_type == DT_DIR && strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0 && strcmp(entry->d_name, ".config") != 0) {
            printf("%s\n", entry->d_name);
        }
    }
    printf("-------------------------\n");
    closedir(dir);
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <path to directory>\n", argv[0]);
        return 1;
    }

    char path[1024];
    strcpy(path, argv[1]);
    struct stat info;

    while (1) {
        list_directories(path);
        if (strcmp(path, "/home/pmi-b1505") == 0) {
            break;
        }
        // Change to the parent directory
        if (stat(path, &info) != 0) {
            perror(path);
            exit(1);
        }
        if (chdir("..") != 0) {
            perror("chdir");
            exit(1);
        }
        if (getcwd(path, sizeof(path)) == NULL) {
            perror("getcwd");
            exit(1);
        }
    }
    printf("Reached the pmi-b1505 directory\n");
    return 0;
}