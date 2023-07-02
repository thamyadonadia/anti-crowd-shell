#ifndef OPERATION_H
#define OPERATION_H

#include <fcntl.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
#include <sys/types.h>

#include "services.h"
#include "signalhandler.h"

/// @brief changes current directory
/// @param path the desired directory
void changeDirectory(char* path);


/// @brief kills background processes, releases memory and terminates acsh
/// @param input structure that holds user input
/// @param sessionLeaders array with sessionLeaders pid
/// @param countLeaders amount of leaders
void exitShell(char* input, int* sessionLeaders, int* countLeaders);

/// @brief executes one background program
/// @param command name of program and it's arguments
/// @return pid of new background process
int backGroundSingleProcess(char* command);

/// @brief executes foreground process
/// @param command name of program and it's arguments
void foreGroundSingleProcess(char* command);

/// @brief executes a group of background programs, separated by <3
/// @param input name and argument of each program, separated by <3
/// @return new session leader pid
int backgroundGroupProcess(char* input);

#endif