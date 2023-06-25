#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <limits.h>

#include "operation.h"
#include "services.h"

int main(int argc, char const *argv[]){
    //system("clear");
    
    char* cwd = malloc(1000 * sizeof(char));
    int countLeaders = 0; int sizeSessionLeaders = 10000; 
    int* sessionLeaders = malloc(sizeSessionLeaders * sizeof(int));
    cwd = getcwd(cwd, 1000);

    while (1){
        char* input = malloc(1000 * sizeof(char)); 
        char* inputCopy = malloc(1000 * sizeof(char));
        shellHeader(cwd);

        //get user input
        input = inputEntry();
        strcpy(inputCopy ,input);
        //find out which type of task it is
        int taskType = taskCaseHandler(input);

        //actually executes the task
        taskPerform(taskType, inputCopy, cwd, sessionLeaders, &countLeaders, &sizeSessionLeaders);

        //pre requisite for inputEntry function
        free(input);
        free(inputCopy);
    }
    
    //essas coisas devem estar no exit?
    free(cwd);
    free(sessionLeaders);
    return 0;
}