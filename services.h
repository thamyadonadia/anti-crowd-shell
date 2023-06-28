#ifndef SERVICES_H
#define SERVICES_H

#include <stdbool.h>

#define CD 0
#define EXIT 1
#define FOREGROUND_PROCESS 3
#define BACKGROUND_SINGLE_PROCESS 4
#define BACKGROUND_GROUP_PROCESS 5

void shellHeader();

char* inputEntry();

int taskCaseHandler(char* command);

void taskPerform(int taskType, char* input, int* sessionLeaders, int* countLeaders, int* sizeSessionLeaders);

bool checkDelimiter(char* input, int len);

bool checkForeground(char* input, int len);

#endif