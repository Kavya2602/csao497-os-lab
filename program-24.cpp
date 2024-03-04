#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
int main() {
    int fd;
    char buffer[1024];
    ssize_t bytes_read, bytes_written;
    fd = creat("testfile.txt", 0644);
    if (fd == -1) {
        perror("Error creating file");
        exit(EXIT_FAILURE);
    }
    printf("File 'testfile.txt' created successfully.\n");
    bytes_written = write(fd, "Hello, this is a test file!\n", 28);
    if (bytes_written == -1) {
        perror("Error writing to file");
        exit(EXIT_FAILURE);
    }
    printf("Data written to file.\n");
    close(fd);
    fd = open("testfile.txt", O_RDONLY);
    if (fd == -1) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }
    bytes_read = read(fd, buffer, sizeof(buffer));
    if (bytes_read == -1) {
        perror("Error reading from file");
        exit(EXIT_FAILURE);
    }
    buffer[bytes_read] = '\0'; 
    printf("Data read from file: %s\n", buffer);
    close(fd);
    if (rename("testfile.txt", "renamedfile.txt") == -1) {
        perror("Error renaming file");
        exit(EXIT_FAILURE);
    }
    printf("File renamed to 'renamedfile.txt'.\n");
    if (unlink("renamedfile.txt") == -1) {
        perror("Error deleting file");
        exit(EXIT_FAILURE);
    }
    printf("File 'renamedfile.txt' deleted.\n");
    return 0;
}
