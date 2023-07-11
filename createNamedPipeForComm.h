#ifndef CREATE_NAMED_FILE_H
#define CREATE_NAMED_FILE_H
#include <sys/types.h>
void createNamedPipeForComm(char* pipeName, int mode, char *msg);
#endif