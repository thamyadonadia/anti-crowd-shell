#ifndef OPERATION_H
#define OPERATION_H


void changeDirectory(char* path, char* cwd);

//must free everything
void exitShell();

void list(char* args);

#endif