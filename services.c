#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

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
 * 3 - processos em background
 * 4 - um único processo
*/
int taskCaseHandler(char* input){
    int len = strlen(input);
    bool delim = checkDelimiter(input);

    char* command = strtok(input, " ");
    char* args = strtok(NULL, " ");

    if(!strcmp(command, "cd")) return 0;
    else if(!strcmp(command, "exit")) return 1;
    else if(!strcmp(command, "ls")) return 2;
    else if(delim) return 3; 
    else return 4;
}

void taskPerform(int taskType, char* input, char* cwd, int* sessionLeaders, int* countLeaders, int* sizeSessionLeaders){
    
    char* inputcpy = strdup(input);
    char* command = strtok(input, " "); char* args = strtok(NULL, " ");

    if(taskType == 0){
        printf("args = %s\n", args);
        changeDirectory(args, cwd);

    }else if(taskType == 1){
        exitShell(inputcpy, sessionLeaders, countLeaders);

    }else if(taskType == 2){
        list(args);

    }else if(taskType == 3){
        int nextLeader = backgroundGroupProcess(inputcpy); *countLeaders++;
        if((*countLeaders)>(*sizeSessionLeaders)) sessionLeaders = realloc(sessionLeaders, (*countLeaders)*3);
        sessionLeaders[(*countLeaders)] = nextLeader;

    } else if(taskType == 4){
        singleProcess(inputcpy);

    } else printf("operações ainda não tratadas!\n");

    free(inputcpy);
}

bool checkDelimiter(char* input){
    int len = strlen(input);

     for(int i=0; i<len; i++){
        //possivel delimitador encontrado
        if(input[i]=='<' && input[i+1]=='3'){
            //confirmação da delimitação e que há outro programa a ser executado
            if(input[i-1]== ' ' && input[i+2]== ' ') return true;
        }
    }

    return false;
}

bool checkForeground(char* input){
    int len = strlen(input);

    for(int i=0; i< len; i++){
        if(input[i] == '%'){
            if(input[i-1]==' ') return true;
        }
    }

    return false;
}
