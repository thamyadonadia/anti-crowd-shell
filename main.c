#include "operation.h"
#include "services.h"
#include "signalhandler.h"


int main(int argc, char const *argv[]){
    system("clear");
    
    signalExecFinished();
    int countLeaders = 0; int sizeSessionLeaders = 10000; 
    int* sessionLeaders = calloc(sizeSessionLeaders, sizeof(int));

    while (1){
        char* input;
        char inputCopy[1000] = "";
        shellHeader();

        //get user input
        input = inputEntry();
        if(!input){
            free(input);
            continue;
        }

        sprintf(inputCopy, "%s", input);
        //finds out which type of task it is
        int taskType = taskCaseHandler(input);

        //executes the task
        taskPerform(taskType, inputCopy, sessionLeaders, &countLeaders, &sizeSessionLeaders);
    }
    return 0;
}