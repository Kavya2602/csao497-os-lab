#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#define SHM_SIZE 1024
#define SHM_NAME "Local\\MySharedMemory"

int main() {
    HANDLE hMapFile;
    LPCTSTR pBuf;

    // Create a shared memory segment
    hMapFile = CreateFileMapping(
        INVALID_HANDLE_VALUE,    // Use the page file
        NULL,                    // Default security
        PAGE_READWRITE,          // Read/write access
        0,                       // High-order DWORD of the maximum size
        SHM_SIZE,                // Low-order DWORD of the maximum size
        SHM_NAME);               // Name of the shared memory object

    if (hMapFile == NULL) {
        perror("CreateFileMapping");
        exit(EXIT_FAILURE);
    }

    // Map the shared memory into the address space
    pBuf = (LPTSTR)MapViewOfFile(
        hMapFile,               // Handle to the map object
        FILE_MAP_ALL_ACCESS,    // Read/write permission
        0,
        0,
        SHM_SIZE);

    if (pBuf == NULL) {
        perror("MapViewOfFile");
        CloseHandle(hMapFile);
        exit(EXIT_FAILURE);
    }

    // Write data to the shared memory
    sprintf((char*)pBuf, "Hello, shared memory!");

    // Fork a new process
    PROCESS_INFORMATION pi;
    STARTUPINFO si;
    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    ZeroMemory(&pi, sizeof(pi));

    if (CreateProcess(NULL,   // No module name (use command line)
                      "child_process.exe",  // Command line
                      NULL,    // Process handle not inheritable
                      NULL,    // Thread handle not inheritable
                      FALSE,   // Set handle inheritance to FALSE
                      0,       // No creation flags
                      NULL,    // Use parent's environment block
                      NULL,    // Use parent's starting directory
                      &si,     // Pointer to STARTUPINFO structure
                      &pi)     // Pointer to PROCESS_INFORMATION structure
        ) {
        // Wait for the child process to finish
        WaitForSingleObject(pi.hProcess, INFINITE);

        // Close process and thread handles
        CloseHandle(pi.hProcess);
        CloseHandle(pi.hThread);
    } else {
        perror("CreateProcess");
    }

    // Print the content of shared memory
    printf("Parent process reads from shared memory: %s\n", pBuf);

    // Unmap the shared memory
    UnmapViewOfFile(pBuf);

    // Close the handle to the shared memory
    CloseHandle(hMapFile);

    return 0;
}

