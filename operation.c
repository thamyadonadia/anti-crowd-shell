#include "operation.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

void changeDirectory(char* path, char* cwd){
    chdir(path);
    //printf("%s\n",getcwd(cwd, 1000));
    getcwd(cwd, 1000);
}

void exitShell(){
    printf("opa, vc está querendo sair do shell?\n");
}

void list(char* args){
    int pid = fork();
    int status;
    if(!pid){
        execv("/bin/ls", &args);
        exit(0);
    }
    else{
        waitpid(pid, &status, 0);
    }
}