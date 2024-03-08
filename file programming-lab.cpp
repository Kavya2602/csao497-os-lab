#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure to represent a disk block
struct DiskBlock {
    char data[512];  // Assume a block size of 512 bytes
    struct DiskBlock* nextBlock;
};

// Structure to represent a file
struct File {
    char filename[50];
    struct DiskBlock* firstBlock;
    struct DiskBlock* lastBlock;
};

// Function to create a new disk block
struct DiskBlock* createDiskBlock() {
    struct DiskBlock* block = (struct DiskBlock*)malloc(sizeof(struct DiskBlock));
    block->nextBlock = NULL;
    return block;
}

// Function to create a new file
struct File* createFile(char* filename) {
    struct File* file = (struct File*)malloc(sizeof(struct File));
    snprintf(file->filename, sizeof(file->filename), "%s", filename);
    file->firstBlock = NULL;
    file->lastBlock = NULL;
    return file;
}

// Function to add a block to the end of a file
void addBlockToFile(struct File* file, struct DiskBlock* block) {
    if (file->lastBlock == NULL) {
        file->firstBlock = block;
        file->lastBlock = block;
    } else {
        file->lastBlock->nextBlock = block;
        file->lastBlock = block;
    }
}

// Function to display the content of a file
void displayFileContent(struct File* file) {
    printf("File: %s\n", file->filename);
    struct DiskBlock* currentBlock = file->firstBlock;
    while (currentBlock != NULL) {
        printf("%s", currentBlock->data);
        currentBlock = currentBlock->nextBlock;
    }
    printf("\n");
}

// Function to append content to a file
void appendToFile(struct File* file, char* content) {
    int contentLength = strlen(content);

    // Simulating disk blocks
    int blockSize = 512;  // Assume a block size of 512 bytes
    int numBlocks = (contentLength / blockSize) + 1;

    for (int i = 0; i < numBlocks; ++i) {
        struct DiskBlock* block = createDiskBlock();
        for (int j = 0; j < blockSize && (i * blockSize + j) < contentLength; ++j) {
            block->data[j] = content[i * blockSize + j];
        }
        addBlockToFile(file, block);
    }
}

int main() {
    struct File* myFile = createFile("sample.txt");

    // Initial content
    char initialContent[] = "This is a sample file content.";
    appendToFile(myFile, initialContent);

    // Displaying initial file content
    displayFileContent(myFile);

    // Appending new content
    char newContent[] = " Appended content.";
    appendToFile(myFile, newContent);

    // Displaying updated file content
    displayFileContent(myFile);

    // Clean up: Free allocated memory
    struct DiskBlock* currentBlock = myFile->firstBlock;
    while (currentBlock != NULL) {
        struct DiskBlock* nextBlock = currentBlock->nextBlock;
        free(currentBlock);
        currentBlock = nextBlock;
    }

    free(myFile);

    return 0;
}

