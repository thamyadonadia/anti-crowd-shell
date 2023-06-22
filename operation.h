#ifndef OPERATION_H
#define OPERATION_H

int getOperation(char* command);

void changeDirectory(char* command, char* path, char* cwd);

void exitShell(char* command);

#endif