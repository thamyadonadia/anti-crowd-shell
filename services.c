#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "services.h"
#include "operation.h"

void shellHeader(char* cd){
    printf("acsh %s> ", cd);
}


char* inputEntry(){
    char* line = NULL;
    size_t len = 0;
    int tam = getline(&line, &len, stdin);

    line[tam-1] = '\0'; //remove newline character

    return line;
}


/**
 * RETORNOS
 * 0 - cd
 * 1 - exit
 * 2 - ls
 * 3 em diante - outros (TODO)
*/
int taskCaseHandler(char* command){
    if(!strcmp(command, "cd")) return 0;
    else if(!strcmp(command, "exit")) return 1;
    else if(!strcmp(command, "ls")) return 2;
    
    //TODO: OUTROS CASOS
    else return 3;
}

void taskPerform(int taskType, char* command, char* args, char* currentDir){
    if(taskType == 0){
        changeDirectory(args, currentDir);
    }
    else if(taskType == 1){
        exitShell();
    }
    else if(taskType == 2){
        list(args);
    }

    else printf("operações ainda não tratadas!\n");
}