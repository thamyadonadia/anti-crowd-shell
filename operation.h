#ifndef OPERATION_H
#define OPERATION_H

void changeDirectory(char* path);

//TODO: LIBERAR PROCESSOS USANDO SINAIS
void exitShell(char* input, int* sessionLeaders, int* countLeaders);

int backGroundSingleProcess(char* command);

void foreGroundSingleProcess(char* command);

int backgroundGroupProcess(char* input);

#endif