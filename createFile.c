#include "createFile.h"

#include <stdio.h>  // cfor input and output operations ie printf scanf
#include <stdlib.h>  // general utilities: exit and atoi
#include <unistd.h>  // API functions :fork, pipe, open, read, write, lseek close
#include <fcntl.h>  // defines constants: O_RDONLY and O_WRONLY O_CREAT  O_TRUNC
#include <sys/types.h> // data types used in system calls : mode_t and off_t
#include <sys/stat.h> //unmask

// Function to create a file with specified permissions
// Input Format: ./a.out createFile ~/myfile.txt 0666
// Output: "File created successfully."

// 0777 always because it is mounted file system

void createFile(char *filename, int permissions)
{
    umask(0);
    // O_WRONLY flag: open a file in write-only mode
    // O_CREAT: if the file doesn't exist, create it
    // O_EXCL: and if it does exist, return error
    // int fd = open(filename, O_WRONLY | O_CREAT | O_EXCL, permissions);      // slashes away w and x perimissions from others and group
    int fd = creat(filename, permissions);
    if (fd == -1) {
        printf("Error creating file");
        exit(1);
    }
    printf("File created successfully.\n");
    close(fd);
}