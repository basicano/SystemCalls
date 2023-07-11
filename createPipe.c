#include "createPipe.h"

#include <stdio.h>  // cfor input and output operations ie printf scanf
#include <stdlib.h>  // general utilities: exit and atoi
#include <unistd.h>  // API functions :fork, pipe, open, read, write, lseek close
#include <fcntl.h>  // defines constants: O_RDONLY and O_WRONLY O_CREAT  O_TRUNC
#include <sys/types.h> // data types used in system calls : mode_t and off_t
#include <sys/stat.h> //unmask

// Function to create a file with specified permissions
// Input Format: ./a.out createPipe ~/myPipe 0666
// Output: "Pipe created successfully."

void createPipe(char *filename, int permissions)
{
    // printf("%o\n", permissions);
    int fd = mknod(filename,  S_IFIFO | permissions, 0); // 0 for device no.
    if (fd == -1) {
        perror("mknod");
        printf("Error creating Pipe\n");
        exit(1);
    }
    printf("Pipe created successfully.\n");
    close(fd);
}