#ifndef SERVICES_H
#define SERVICES_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>

#include "operation.h"

#define CD 0
#define EXIT 1
#define FOREGROUND_PROCESS 3
#define BACKGROUND_SINGLE_PROCESS 4
#define BACKGROUND_GROUP_PROCESS 5

/// @brief only a print
void shellHeader();

/// @brief gets the input line from user, without \n
/// @return input command from user
char* inputEntry();

/// @brief decides which task it is
/// @param input the user command, from inputEntry
/// @return the task, as an int
int taskCaseHandler(char* command);


/// @brief executes the task, using operation.h
/// @param taskType output from taskCaseHandler
/// @param input user input
/// @param sessionLeaders array that holds pid from all session leaders outputed from background
/// @param countLeaders amount of background leaders
/// @param sizeSessionLeaders current size of sessionLeaders
void taskPerform(int taskType, char* input, int* sessionLeaders, int* countLeaders, int* sizeSessionLeaders);


/// @brief checks if there is <3 in user input
/// @param input the user input
/// @param len length from user input
/// @return true, if there is <3, false if not
bool checkDelimiter(char* input, int len);


/// @brief checks if there is % in user input
/// @param input the user input
/// @param len length from user input
/// @return true, if there is %, false if not
bool checkForeground(char* input, int len);

#endif