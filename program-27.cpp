#include <stdio.h>
#include <dirent.h>

int main(int argc, char* argv[]) {
    char* dir_name = ".";
    if (argc == 2) {
        dir_name = argv[1];
    }
    DIR* dir = opendir(dir_name);
    if (dir == NULL) {
        perror("Error opening directory");
        return 1;
    }
    struct dirent* dir_entry;
    while ((dir_entry = readdir(dir)) != NULL) {
        printf("%s\n", dir_entry->d_name);
    }
    closedir(dir);
    return 0;
}
