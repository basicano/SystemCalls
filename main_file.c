#include <stdio.h>  // cfor input and output operations ie printf scanf
#include <stdlib.h>  // general utilities: exit and atoi
#include <unistd.h>  // API functions :fork, pipe, open, read, write, lseek close
#include <fcntl.h>  // defines constants: O_RDONLY and O_WRONLY O_CREAT  O_TRUNC
#include <sys/types.h> // data types used in system calls : mode_t and off_t
#include <string.h> // for strcmp

// Task: create a file
#include "createFile.h"
// Task: create a named pipe
#include "createPipe.h"
// Task: read data from a file
#include "readFileData.h"
// Task: write data from a file
#include "writeFileData.h"
// Task: display status of file
#include "displayFileStats.h"
// Task: Create an unnamed pipe designed for copying a file's content
#include "copyUsingPipe.h"
// Task: Create a named pipe to help communicate between two processes
#include "createNamedPipeForComm.h"

int main(int argc, char* argv[]) {
    if (argc < 2) {
        printf("Error, insufficient parameters, please enter parameters in the following format: %s createFile <task> [arguments]\n", argv[0]);
        return 0;
    }

    char* task = argv[1];

    if (strcmp(task, "createFile") == 0){   // Create file
        if (argc < 4) {
            printf("Error, insufficient parameters. Format expected: %s createFile <file name> <permissions>\n", argv[0]);
            return 0;
        }
        
        // strtol:  to convert the permission provided as a string to an integer value 
    
        char* fileName = argv[2];
        int permissions = strtol(argv[3], NULL, 8); // 8: Number Base (Octal-format'0666')
        createFile(fileName, permissions);
    }

    if (strcmp(task, "createPipe") == 0){   // Create pipe
        if (argc < 4) {
            printf("Error, insufficient parameters. Format expected: %s createPipe <pipe_name> <permissions>\n", argv[0]);
            return 0;
        }
        
        // strtol:  to convert the permission provided as a string to an integer value 
    
        char* pipeName = argv[2];
        int permissions = strtol(argv[3], NULL, 8); // 8: Number Base (Octal-format'0666')
        createPipe(pipeName, permissions);
    }    

    else if(strcmp(task, "read") == 0){
        if (argc < 5) {
            printf("Error, insufficient parameters. Format expected: %s read <file name> <offset> <amt2read>\n", argv[0]);
            return 0;
        }

        char* fileName = argv[2];
        int offset = atoi(argv[3]);
        int amt2read = atoi(argv[4]);
        readFileData(fileName, offset, amt2read);
    }

    else if(strcmp(argv[1], "write") == 0){
        if (argc < 5) {
            printf("Error, insufficient parameters. Format expected: %s write <file name> <offset> <amt2write> <data>\n", argv[0]);
            return 0;
        }

        char* fileName = argv[2];
        int offset = atoi(argv[3]);
        char* data = argv[4];
        writeFileData(fileName, offset, data);
    }

    else if(strcmp(argv[1], "displayStats") == 0){
        if (argc < 3) {
            printf("Error, insufficient parameters. Format expected: %s displayStats <file name> \n", argv[0]);
            return 0;
        }
        char* fileName = argv[2];
        displayFileStats(fileName);
    }

    else if(strcmp(argv[1], "copyUsingPipe") == 0){
        if (argc < 4) {
            printf("Error, insufficient parameters. Format expected: %s copyUsingPipe <sourceFile> <destinationFile>\n", argv[0]);
            return 0;
        }

        char* sourceFile = argv[2];
        char* destinationFile = argv[3];
        copyUsingPipe(sourceFile, destinationFile);
    }

    else if(strcmp(argv[1], "commUsingNamedPipe") == 0){
        if (argc < 4) {
            printf("Error, insufficient parameters. Format expected:  %s commUsingNamedPipe <pipe name> <mode> //ifwritemode<msg>\n", argv[0]);
            return 0;
        }

            char* pipeName = argv[2];
            int mode = atoi(argv[3]);
            char* msg = "";
            
            if(mode == O_WRONLY){
                if(argc <5){
                    printf("Error, insufficient parameters. Format expected:  %s commUsingNamedPipe <pipe name> <mode> <msg>\n", argv[0]);
                }
                msg = argv[4];
            }
            createNamedPipeForComm(pipeName, mode, msg);
    }
    
    return 0;
}