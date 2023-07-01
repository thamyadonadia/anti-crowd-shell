#ifndef SIGNALHANDLER_H
#define SIGNALHANDLER_H

void signalHandlerPrint(int signum);
void signalHandlerNoPrint(int signum);

void signalExecDefault();
void signalExecRunning();
void signalExecFinished();


#endif