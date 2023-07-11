#include "readFileData.h"

#include <stdio.h>  // cfor input and output operations ie printf scanf
#include <stdlib.h>  // general utilities: exit and atoi
#include <unistd.h>  // API functions :fork, pipe, open, read, write, lseek close
#include <fcntl.h>  // defines constants: O_RDONLY and O_WRONLY O_CREAT  O_TRUNC
#include <sys/types.h> // data types used in system calls : mode_t and off_t
#include <sys/stat.h> // retrieving information about file status and file permissions: stat and chmod.

// Function to read data from a file starting from a specified offset and of a specified size
// Input Format: ./a.out read file1.txt 5 100
// Output: "File data read from file: <data read>"

void readFileData(char* fileName, int offset, int size) {
    // O_RDONLY: open file in read only mode
    int fd = open(fileName, O_RDONLY);
    if (fd == -1) {
        perror("Error in opening file: File doesnot exit. Exiting... ");
        exit(1);					
    }

    // SEEK_SET: relative to the beginning of the file
    // offset: the byte no. read pointer should move to 
    if (lseek(fd, offset, SEEK_SET) == -1) {
        perror("Error seeking file: offset claculation might have exceeded the limits of the file size. Exiting ...");
        close(fd);
        exit(1);					// signifies that the application failed
    }

    char* buffer = (char*)malloc(size+1);     // allocate memory of size: amount to read
    int bytesRead = read(fd, buffer, size);  // read data from a file 
    if (bytesRead == -1) {
        perror("Error reading from file");
        close(fd);
        free(buffer);   // free dynamically allocated memory
        exit(1);
    }
    buffer[bytesRead] = '\0';
    printf("File data read from file: %s\n", buffer);

    close(fd);
    free(buffer);  // free dynamically allocated memory
}
