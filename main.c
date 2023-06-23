#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <limits.h>

#include "operation.h"
#include "services.h"

int main(int argc, char const *argv[]){
    system("clear");
    
    char* input, cwd = malloc(sizeof(char)*1000);
    getcwd(cwd, sizeof(cwd)); 

    while (1){
        shellHeader(cwd);

        //get user input
        input = inputEntry();

        //find out which type of task it is
        int taskType = taskCaseHandler(input);

        //actually executes the task
        taskPerform(taskType, input, cwd);

        //pre requisite for inputEntry function
        free(input);
    }
    
    free(cwd);
    return 0;
}