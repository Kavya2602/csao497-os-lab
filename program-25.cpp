#include <stdio.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>

int main() {
    int fd = open("example.txt", O_RDWR | O_CREAT, 0644);
    if (fd != -1) {
        close(fd);
    }
    fd = open("example.txt", O_RDONLY);
    if (fd != -1) {
        off_t offset = lseek(fd, 10, SEEK_SET); 
        close(fd);
    }
    struct stat file_info;
    if (stat("example.txt", &file_info) == 0) {
        printf("File size: %ld bytes\n", file_info.st_size);
    }
    DIR *dir = opendir(".");
    if (dir != NULL) {
        struct dirent *entry;
        while ((entry = readdir(dir)) != NULL) {
            printf("Entry name: %s\n", entry->d_name);
        }
        closedir(dir);
    }
    return 0;
}
