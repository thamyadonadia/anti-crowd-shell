#include "operation.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

int getOperation(char* command){
    if(!strcmp(command, "cd")) return 1;
    if(!strcmp(command, "exit")) return 2; 
}

void changeDirectory(char* command, char* path, char* cwd){
    if(!strcmp(path, "..")){
        int i, slashCounter = 0;

        for(i=0; i< strlen(cwd); i++){
            if(cwd[i] == '/') slashCounter++;
        } 
            
        for(i=0; i<strlen(cwd); i++){
            if(cwd[i] == '/') slashCounter--;

            if(slashCounter == 0){
                printf("for counter i=%d\n", i);
                strncpy(cwd, cwd, i-1);
                break;
            }   
        }
        printf("%s\n", cwd);
       // chdir(cwd);

    }//else if(!strcmp(path, NULL)) return; // cd vazio

    //strcat(cwd, "/"); strcat(cwd, path);
    //strncpy(cwd, cwd, strlen(cwd-1));
    //chdir(cwd);
}

void exitShell(char* command){
    printf("opa, vc está querendo sair do shell?\n");
}
