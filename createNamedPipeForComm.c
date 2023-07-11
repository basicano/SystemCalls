#include "createNamedPipeForComm.h"

#include <stdio.h>  // cfor input and output operations ie printf scanf
#include <stdlib.h>  // general utilities: exit and atoi
#include <unistd.h>  // API functions :fork, pipe, open, read, write, lseek close
#include <fcntl.h>  // defines constants: O_RDONLY and O_WRONLY O_CREAT  O_TRUNC
#include <string.h>

// Function to create a named pipe for communication between two processes
// Input (Reading Process): ./a.out commUsingNamedPipe ~/myPipe 0
// Output: Data is now written to the named pipe!
// Input(Writing Process): ./a.out commUsingNamedPipe ~/myPipe 1 "This is a message for reading process"
// Output: Data read from the pipe: This is a message for reading process

void createNamedPipeForComm(char* pipeName, int mode, char* msg) {  

	if(mode == O_RDONLY){
		// open named pipe for reading

		int fd = open(pipeName, O_RDONLY);
		if (fd == -1){
			printf("Error opening named pipe for reading. Exiting...\n");
			exit(1);
		}

		char buffer[1024];
        int bytesRead;

		bytesRead = read(fd, buffer, 1024);

		// while(bytesRead = read(fd, buffer, 1024)){
			// printf("Data read from the pipe: %s\n", buffer);
		// }

		if (bytesRead == -1) {
            perror("Error in reading from named pipe. Exiting...");
            close(fd);
            exit(1);
        }

		printf("Data read from the pipe: %s\n", buffer);
		close(fd);
	}
	else if(mode == O_WRONLY){
		int fd = open(pipeName, O_WRONLY);
		if (fd == -1) {
            perror("Error in openeing named pipe. Exiting ...");
            exit(1);
        }

        int bytesWritten = write(fd, msg, strlen(msg));

        if (bytesWritten == -1) {
            perror("Error in writing to named pipe. Exiting ...");
            close(fd);
            exit(1);
        }

        printf("Data is now written to the named pipe!");
		close(fd);
	}
	else{
		printf("Invalid pipe mode specified.\n");
        exit(1);
	}
}

