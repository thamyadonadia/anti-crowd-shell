#ifndef SERVICES_H
#define SERVICES_H

void shellHeader(char* cd);

char* inputEntry();

int taskCaseHandler(char* command);

void taskPerform(int taskType, char* command, char* args, char* currentDir);


#endif