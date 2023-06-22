#include "operation.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void changeDirectory(char* command){
    strcat(command, " && ls");
    printf("%s\n", command);
    system(command);
    return;
}