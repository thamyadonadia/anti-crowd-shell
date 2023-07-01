#include "signalhandler.h"
#include "services.h"

#include <stdio.h>
#include <signal.h>
#include<unistd.h>


void signalHandlerPrint(int signum){
    printf("\nNão adianta me enviar o sinal por Ctrl-... . Estou vacinado!\nacsh>");
    sleep(1);
    return;
}
void signalHandlerNoPrint(int signum){
    printf("\n");
    return;
}

void signalExecDefault(){
    signal(SIGINT, SIG_DFL);
    signal(SIGQUIT, SIG_DFL);
    signal(SIGTSTP, SIG_DFL);
}

void signalExecRunning(){
    signal(SIGINT, signalHandlerNoPrint);
    signal(SIGQUIT, signalHandlerNoPrint);
    signal(SIGTSTP, signalHandlerNoPrint);
}

void signalExecFinished(){
    signal(SIGINT, signalHandlerPrint);
    signal(SIGQUIT, signalHandlerPrint);
    signal(SIGTSTP, signalHandlerPrint);
}
