#include "writeFileData.h"

#include <stdio.h>  // cfor input and output operations ie printf scanf
#include <stdlib.h>  // general utilities: exit and atoi
#include <unistd.h>  // API functions :fork, pipe, open, read, write, lseek close
#include <fcntl.h>  // defines constants: O_RDONLY and O_WRONLY O_CREAT  O_TRUNC
#include <sys/types.h> // data types used in system calls : mode_t and off_t
#include <string.h>

// Function to write data to a file starting from a specified offset
// Input Format: ./program write file1.txt 4 "Lorem Ipsum"
// Data is now written in file file1.txt 

void writeFileData(char* fileName, int offset, char* data) {
    // open file in write only mode
    int fd = open(fileName, O_WRONLY);
    if (fd == -1) {
        perror("Error in opening file: File doesnot exit. Exiting...");
        exit(1);
    }

    // SEEK_SET: relative to the beginning of the file
    // offset: the byte no. read pointer should move to 
    if (lseek(fd, offset, SEEK_SET) == -1) {
        perror("Error seeking file: offset claculation might have exceeded the limits of the file size. Exiting ...");
        close(fd);
        exit(1);
    }

    int bytesWritten = write(fd, data, strlen(data));
    if (bytesWritten == -1) {
        perror("Error in writing to file. Exiting ... ");
        close(fd);
        exit(1);
    }

    printf("Data is now written in file %s \n",  fileName);
    close(fd);
}
