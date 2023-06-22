#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <limits.h>

#include "operation.h"

int main(int argc, char const *argv[]){
    system("clear");
    char* command = NULL;
    size_t len = 0;

    char currentDirectory[1000];
    getcwd(currentDirectory, sizeof(currentDirectory)); 

    while (1)
    {
        printf("acsh %s > ", currentDirectory);
        int tam = getline(&command, &len, stdin);

        // printf("%s", command);
        // TODO: CRIME CRIME ALO CRIME
        command[tam-1] = '\0';
        changeDirectory(command, currentDirectory);

        free(command);
        char* command = NULL;
        size_t len = 0;
    }
    
    return 0;
}