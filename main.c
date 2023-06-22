#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "operation.h"

int main(int argc, char const *argv[]){
    system("clear"); 
    printf("acsh> ");  

    char* command; size_t len;
    int tam = getline(&command, &len, stdin);   

    // TODO: CRIME CRIME ALO CRIME  
    command[tam-1] = '\0';
    changeDirectory(command);

    free(command);
    return 0;
}