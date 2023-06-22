#include "operation.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>


void changeDirectory(char* command, char* cwd){
    //strcat(command, " && ls");
    
    

    printf("%s", command);

    getcwd(cwd, sizeof(cwd));
    return;
}