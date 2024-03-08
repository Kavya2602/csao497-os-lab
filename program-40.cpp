#include <stdio.h>
#ifdef _WIN32
#include <Windows.h>
#else
#include <sys/stat.h>
#include <unistd.h>
#endif

int main() {
    char filename[100];

    printf("Enter the filename: ");
    scanf("%s", filename);

#ifdef _WIN32
    // Windows specific code
    DWORD attributes = GetFileAttributes(filename);
    if (attributes == INVALID_FILE_ATTRIBUTES) {
        printf("Error: Unable to get file attributes.\n");
        return 1;
    }

    printf("File: %s\n", filename);
    printf("Owner permissions: %s\n", (attributes & FILE_ATTRIBUTE_READONLY) ? "r" : "-");
    printf("Group permissions: %s\n", (attributes & FILE_ATTRIBUTE_DIRECTORY) ? "d" : "-");
    printf("Others permissions: %s\n", (attributes & FILE_ATTRIBUTE_HIDDEN) ? "h" : "-");
#else
    // Linux specific code
    struct stat fileStat;

    if (stat(filename, &fileStat) < 0) {
        printf("Error: Unable to get file status.\n");
        return 1;
    }

    printf("File: %s\n", filename);
    printf("Owner permissions: %c%c%c\n",
           (fileStat.st_mode & S_IRUSR) ? 'r' : '-',
           (fileStat.st_mode & S_IWUSR) ? 'w' : '-',
           (fileStat.st_mode & S_IXUSR) ? 'x' : '-');
    printf("Group permissions: %c%c%c\n",
           (fileStat.st_mode & S_IRGRP) ? 'r' : '-',
           (fileStat.st_mode & S_IWGRP) ? 'w' : '-',
           (fileStat.st_mode & S_IXGRP) ? 'x' : '-');
    printf("Others permissions: %c%c%c\n",
           (fileStat.st_mode & S_IROTH) ? 'r' : '-',
           (fileStat.st_mode & S_IWOTH) ? 'w' : '-',
           (fileStat.st_mode & S_IXOTH) ? 'x' : '-');
#endif

    return 0;
}
