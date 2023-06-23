#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <limits.h>

#include "operation.h"
#include "services.h"

int main(int argc, char const *argv[]){
    system("clear");

    char* input;

    char currentDirectory[1000];
    getcwd(currentDirectory, sizeof(currentDirectory)); 

    while (1){
        shellHeader(currentDirectory);

        //get user input
        input = inputEntry();

        char* command = strtok(input, " ");
        char* args = strtok(NULL, " ");

        //find out which type of task it is
        int taskType = taskCaseHandler(command);

        //actually executes the task
        taskPerform(taskType, command, args, currentDirectory);

        //pre requisite for inputEntry function
        free(input);
    }
    
    return 0;
}