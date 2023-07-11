#include "displayFileStats.h"

#include <stdio.h>  // cfor input and output operations ie printf scanf
#include <stdlib.h>  // general utilities: exit and atoi
#include <sys/types.h> // data types used in system calls : mode_t and off_t
#include <sys/stat.h> // retrieving information about file status and file permissions: stat and chmod.
#include <time.h> //converting a time value to a string representation

// Function to display file statistics including owner, permissions, inode, and timestamps
// Input Format: ./a.out displayStats file1.txt
// Output: 
// File Statistics Information for file 'file1.txt':
// Owner: 1000
// Permissions: 100777
// Inode: 178173660257910177
// Last Access Time: Tue Jul  4 00:24:15 2023
// Last Modification Time: Tue Jul  4 00:24:15 2023
// Last Status Change Time: Tue Jul  4 00:24:15 2023

void displayFileStats(char* fileName) {
    struct stat fileStats;
    if (stat(fileName, &fileStats) == -1) {
        perror("Error in getting file stats");
        exit(1);
    }

    printf("File Statistics Information for file '%s':\n", fileName);
    printf("Owner: %d\n", fileStats.st_uid);
    printf("Permissions: %o\n", fileStats.st_mode);
    printf("Inode: %lu\n", fileStats.st_ino);
    printf("Last Access Time: %s", ctime(&fileStats.st_atime));
    printf("Last Modification Time: %s", ctime(&fileStats.st_mtime));
    printf("Last Status Change Time: %s", ctime(&fileStats.st_ctime));
}
