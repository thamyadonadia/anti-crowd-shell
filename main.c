#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <limits.h>

#include "operation.h"

int main(int argc, char const *argv[]){
    system("clear");

    char* line = NULL; size_t len = 0;

    char currentDirectory[1000];
    getcwd(currentDirectory, sizeof(currentDirectory)); 

    while (1){
        printf("acsh %s > ", currentDirectory);
        int tam = getline(&line, &len, stdin);
        line[tam-1] = '\0'; // TODO: CRIME CRIME ALO CRIME

        char* command = strtok(line, " "); 
        char* args = strtok(NULL, " ");

        // acho que vale a pena tirar da main rs
        if(getOperation(command) == 1){
            changeDirectory(command, args, currentDirectory);

        }else if(getOperation(command) == 2){
            printf("%s\n", line);
            exitShell(command);

        }

        free(line);
        char* line = NULL; size_t len = 0;
    }
    
    return 0;
}