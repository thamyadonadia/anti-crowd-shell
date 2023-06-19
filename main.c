#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#include "operation.h"

int main(int argc, char const *argv[]){
    system("clear"); 
    printf("acsh> ");  

    char* command = malloc(sizeof(char)*100);
    size_t len = 100;
    getline(&command, &len, stdin);
    changeDirectory(command);

    free(command);
    return 0;
}
