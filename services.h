#ifndef SERVICES_H
#define SERVICES_H
#include <stdbool.h>

void shellHeader(char* cd);

char* inputEntry();

int taskCaseHandler(char* command);

void taskPerform(int taskType, char* input, char* cwd, int* sessionLeaders, int* countLeaders, int* sizeSessionLeaders);

bool checkDelimiter(char* input);

bool checkForeground(char* input);

#endif