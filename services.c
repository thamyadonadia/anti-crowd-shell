#include "services.h"


void shellHeader(){
    printf("acsh> ");
}


char* inputEntry(){
    char* line = NULL; size_t len = 0;
    char* output;
    if(getline(&line, &len, stdin) != -1) output = strtok(line, "\n");
    free(line);
    return output;
}


int taskCaseHandler(char* input){
    int len = strlen(input);
    bool delim = checkDelimiter(input, len);
    bool foreground = checkForeground(input, len);
    
    char* command = strtok(input, " ");

    if(!strcmp(command, "cd")) return CD;
    else if(!strcmp(command, "exit")) return EXIT;
    else if(foreground) return FOREGROUND_PROCESS;
    else if(delim) return BACKGROUND_GROUP_PROCESS; 
    else return BACKGROUND_SINGLE_PROCESS; 
}

void taskPerform(int taskType, char* input, int* sessionLeaders, int* countLeaders, int* sizeSessionLeaders){
    char* inputCopy = strdup(input);
    char* command = strtok(input, " "); 
    command = strtok(NULL, " ");

    if(taskType == CD){
        changeDirectory(command);

    }else if(taskType == EXIT){
        exitShell(inputCopy, sessionLeaders, countLeaders);
        
    } else if(taskType == FOREGROUND_PROCESS){
        foreGroundSingleProcess(inputCopy);

    //in next cases, there is a need to keep pid of processes in new session
    } else if(taskType == BACKGROUND_SINGLE_PROCESS){
        int nextLeader = backGroundSingleProcess(inputCopy);
        (*countLeaders)++;
        if((*countLeaders)>(*sizeSessionLeaders)) sessionLeaders = realloc(sessionLeaders, (*countLeaders)*3);
        sessionLeaders[(*countLeaders)-1] = nextLeader;

    } else if(taskType == BACKGROUND_GROUP_PROCESS){ 
        int nextLeader = backgroundGroupProcess(inputCopy);
        (*countLeaders)++;
        if((*countLeaders)>(*sizeSessionLeaders)) sessionLeaders = realloc(sessionLeaders, (*countLeaders)*3);
        sessionLeaders[(*countLeaders)-1] = nextLeader;

    } else printf("ERROR: Operation not found!\n");
    free(inputCopy);
}

bool checkDelimiter(char* input, int len){
    for(int i=0; i<len; i++){
        //possible <3 found
        if(input[i]=='<' && input[i+1]=='3'){
            // <3 confirmed 
            if(input[i-1]== ' ' && input[i+2]== ' ') return true;
        }
    }
    return false;
}

bool checkForeground(char* input, int len){
    for(int i=0; i< len; i++){
        //possible % found
        if(input[i] == '%'){ 
            //%confirmed
            if(input[i-1]==' ') return true; 
        }
    }
    return false;
}