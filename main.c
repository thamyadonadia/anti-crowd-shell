#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <limits.h>

#include "operation.h"
#include "services.h"

int main(int argc, char const *argv[]){
    system("clear");
    
    char* input; char* cwd = malloc(sizeof(char)*1000);
    char* inputCopy;
    int countLeaders = 0; int sizeSessionLeaders = 10000; int* sessionLeaders = malloc(sizeof(int)*sizeSessionLeaders);
    getcwd(cwd, sizeof(cwd)); 

    while (1){
        shellHeader(cwd);

        //get user input
        input = inputEntry();
        inputCopy = strdup(input);
        //find out which type of task it is
        int taskType = taskCaseHandler(input);

        //actually executes the task
        taskPerform(taskType, inputCopy, cwd, sessionLeaders, &countLeaders, &sizeSessionLeaders);

        //pre requisite for inputEntry function
        free(input);
        free(inputCopy);
    }
    
    free(cwd);
    free(sessionLeaders);
    return 0;
}