#include "copyUsingPipe.h"

#include <stdio.h>  // cfor input and output operations ie printf scanf
#include <stdlib.h>  // general utilities: exit and atoi
#include <unistd.h>  // API functions :fork, pipe, open, read, write, lseek close
#include <fcntl.h>  // defines constants: O_RDONLY and O_WRONLY O_CREAT  O_TRUNC
#include <sys/types.h> // data types used in system calls : mode_t and off_t
#include <sys/wait.h>  // For wait function


// Function to copy the content of a source file to a destination file using a pipe
// Input: ./a.out copyUsingPipe file1.txt file2.txt
// Output: File data from file1.txt copied to file file2.txt sucessfully!!

void copyUsingPipe(char* sourceFile, char* destinationFile) {
    // stores the 2 file descriptors: pipefd[0]: for reading and pipefd[1]: for writing
    int pipefd[2];

    // attempting to create pipe
    if (pipe(pipefd) == -1) {
        perror("Error in creating pipe. Exiting...");
        exit(1);							// signifies that the application failed
    }

    /*
    child process: read from sourceFile and write to pipe(pipefd[1])
    parent process: read from pipe(pipefd[0]) and write to destinationFile 
    */

    int pid = fork();
    if (pid == -1) {
        perror("Error in fork() command.");
        exit(1);
    } 
    else if (pid == 0) {
        // Child Process : performs writing to pipe

        close(pipefd[0]);  // Close read pipefd

        int sourcefd = open(sourceFile, O_RDONLY);
        if (sourcefd == -1) {
            perror("Error in opening source file. Exiting ...");
            exit(1);							
        }	

        char buffer[1024];
        int bytesRead;
        while (( bytesRead = read(sourcefd, buffer, 1024) ) > 0) {
            int bytesWritten = write(pipefd[1], buffer, bytesRead);
            if (bytesWritten == -1) {
                perror("Error in writing to pipe. Exiting ..");
                close(sourcefd);
                close(pipefd[1]);
                exit(1);
            }
        }
        
        close(sourcefd);
        close(pipefd[1]);  // Close write pipefd
        exit(0);
    } 
    else {
        // Parent process : reading from pipe
        close(pipefd[1]);  // Close unused write end

        int destinationfd = open(destinationFile, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
        if (destinationfd == -1) {
            perror("Error in opening destination file");
            exit(1);
        }

        char buffer[1024];
        int bytesRead;
        while ((bytesRead = read(pipefd[0], buffer, sizeof(buffer))) > 0) {
            int bytesWritten = write(destinationfd, buffer, bytesRead);
            if (bytesWritten == -1) {
                perror("Error writing to destination file");
                close(destinationfd);
                close(pipefd[0]);
                exit(1);
            }
        }

        close(destinationfd);
        close(pipefd[0]);
        wait(NULL);  // Wait for the child process to finish
    }

    printf("File data from %s copied to file %s sucessfully!!\n", sourceFile, destinationFile);
}
