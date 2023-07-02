#ifndef SIGNALHANDLER_H
#define SIGNALHANDLER_H


#include <stdio.h>
#include <unistd.h>
#include <signal.h>


/// @brief signal Handler that prints
/// @param signum code of catched signal
void signalHandlerPrint(int signum);


/// @brief signal Handler that does not print
/// @param signum code of catched signal
void signalHandlerNoPrint(int signum);


/// @brief applies default signal treatment to SIGINT, SIGQUIT and SIGTSTP
void signalExecDefault();


/// @brief applies no printing signal treatment to SIGINT, SIGQUIT and SIGTSTP
void signalExecRunning();


/// @brief applies printing signal treatment to SIGINT, SIGQUIT and SIGTSTP
void signalExecFinished();


#endif