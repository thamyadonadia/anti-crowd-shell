#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>

#include "services.h"
#include "operation.h"

void shellHeader(){
    printf("acsh> ");
}

char* inputEntry(){
    char* line = NULL; size_t len = 0;
    if(getline(&line, &len, stdin)!=-1) line = strtok(line, "\n");
    return line;
}

int taskCaseHandler(char* input){
    int len = strlen(input);
    bool delim = checkDelimiter(input, len);
    bool foreground = checkForeground(input, len);
    
    char* command = strtok(input, " ");
    char* args = strtok(NULL, " ");

    if(!strcmp(command, "cd")) return CD;
    else if(!strcmp(command, "exit")) return EXIT;
    else if(foreground) return FOREGROUND_PROCESS;
    else if(delim) return BACKGROUND_GROUP_PROCESS; 
    else return BACKGROUND_SINGLE_PROCESS; 
}

void taskPerform(int taskType, char* input, int* sessionLeaders, int* countLeaders, int* sizeSessionLeaders){
    char* inputCopy = strdup(input);
    char* command = strtok(input, " "); char* args = strtok(NULL, " ");

    if(taskType == CD){
        changeDirectory(args);

    }else if(taskType == EXIT){
        exitShell(inputCopy, sessionLeaders, countLeaders);
        
    } else if(taskType == FOREGROUND_PROCESS){
        foreGroundSingleProcess(inputCopy);

    } else if(taskType == BACKGROUND_SINGLE_PROCESS){
        int nextLeader = backGroundSingleProcess(inputCopy);
        (*countLeaders)++;
        if((*countLeaders)>(*sizeSessionLeaders)) sessionLeaders = realloc(sessionLeaders, (*countLeaders)*3);
        sessionLeaders[(*countLeaders)] = nextLeader;

    } else if(taskType == BACKGROUND_GROUP_PROCESS){ 
        int nextLeader = backgroundGroupProcess(inputCopy); 
        (*countLeaders)++;
        if((*countLeaders)>(*sizeSessionLeaders)) sessionLeaders = realloc(sessionLeaders, (*countLeaders)*3);
        sessionLeaders[(*countLeaders)] = nextLeader;

    } else printf("ERROR: Operation not found!\n");

    free(inputCopy);
    sleep(1); //apenas para que o header apareça normalmente
}

bool checkDelimiter(char* input, int len){
    for(int i=0; i<len; i++){
        //possivel operador especial encontrado
        if(input[i]=='<' && input[i+1]=='3'){
            //confirmação da existência do operador especial
            if(input[i-1]== ' ' && input[i+2]== ' ') return true;
        }
    }

    return false;
}

bool checkForeground(char* input, int len){
    for(int i=0; i< len; i++){
        //possivel operador especial encontrado
        if(input[i] == '%'){ 
            //confirmação da existência do operador especial
            if(input[i-1]==' ') return true; 
        }
    }

    return false;
}
