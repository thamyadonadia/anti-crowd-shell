#include "operation.h"


// ========== Internal Operations ============ //

void changeDirectory(char* path){
    if(path == NULL) chdir("/");
    if((chdir(path) == -1) && (errno == ENOENT)) printf("ERROR: Directory or file not found!\n");
}

void exitShell(char* input, int* sessionLeaders, int* countLeaders){
    //terminates background processes still running
    for(int i=0; i<(*countLeaders); i++){
        kill(sessionLeaders[i]*(-1), SIGKILL);
    }
    //releases dynamic memory
    free(sessionLeaders);
    free(input);
    exit(0);
}

// =========== Program execution ========== //

void foreGroundSingleProcess(char* command){
    char* filename; int i=0; pid_t pid;
    char* args[5] = {NULL, NULL, NULL, NULL, NULL}; 

    //creates new process
    pid = fork();

    if(!pid){ //in child process
        filename = strtok(command, " ");

        while(args[i] && i<2){
            args[i] = strtok(NULL, " "); i++; 
        }
        signalExecDefault();
        execvp(filename, args);
    }

    else { //in acsh
        signalExecRunning();
        waitpid(pid, NULL, WUNTRACED);
        signalExecFinished();
    }
}

int backGroundSingleProcess(char* command){
    char* filename; int i=1; pid_t pid;
    char* args[5] = {NULL, NULL, NULL, NULL, NULL}; 
    pid = fork();

    if(!pid){ //in child process
        filename = strtok(command, " ");
        args[0] = filename;

        while(args[i] && i<3){
            args[i] = strtok(NULL, " "); 
        }

        setsid();

        //avoids printing in acsh terminal
        int devNull = open("/dev/null", O_RDWR);
        dup2(devNull, STDIN_FILENO);
        dup2(devNull, STDOUT_FILENO);
        close(devNull);

        if(execvp(filename, args) == -1) exit(errno);
    }
    return pid;
}


int backgroundGroupProcess(char* input){
    //loop variables
    int len = strlen(input);
    int k=0, inicio=0;

    char* processLeader = malloc(sizeof(char) * strlen(input)); 
    char* filenameLeader; 
    char* argsLeader[5] = {NULL, NULL, NULL, NULL, NULL};
            
    //collects leader process name and arguments
    for(int i=0; i<= len; i++){
        //finds <3 position
        if(((i != len-1) && (input[i] == '<' && input[i+1] == '3')) || input[i] == '\0'){
            if(input[i-1]==' ' || input[i]=='\0'){
               //copy everything
                for(int j=inicio; j<i; j++){
                    processLeader[k] = input[j];
                    k++;
                }
                
                int l=0;
                filenameLeader = strtok(processLeader, " "); 
                argsLeader[0] = filenameLeader;
                argsLeader[l] = strtok(NULL, " ");

                while(argsLeader[l] && l<3){
                    l++;
                    argsLeader[l] = strtok(NULL, " "); 
                }
                //updates loop variables
                inicio = i+3; k=0; 
                break;
            }
        }
    }

    pid_t leader = fork(); 
    pid_t pid;
    if(leader == 0){ // in child leader process
       setsid(); //new session

        //avoids printing in acsh terminal
        int devNull = open("/dev/null", O_RDWR);
        dup2(devNull, STDIN_FILENO);
        dup2(devNull, STDOUT_FILENO);
        close(devNull);

        //repeats the loop for each remaining process in the input line
        for(int i=inicio; i<=len; i++){
            if(((i != len-1) && (input[i] == '<' && input[i+1] == '3')) || input[i] == '\0'){
                if(input[i-1]==' ' || input[i]=='\0'){
                    char* process = malloc(sizeof(char) * strlen(input));

                    for(int j=inicio; j<i; j++){
                        process[k] = input[j];
                        k++;
                    }

                    char* filename = strtok(process, " "); char* args[5] = {NULL, NULL, NULL, NULL, NULL};
                    args[0] = filename;
                    int l=1; args[l] = strtok(NULL, " ");

                    while(args[l] && l<3){
                        l++; 
                        args[l] = strtok(NULL, " "); 
                    }

                    inicio = i+3; k=0;
                    //creates the new process and executes it in leader session
                    pid = fork();
                    
                    if(pid==0){
                        if(execvp(filename, args) == -1) exit(errno); 
                        
                    }else{
                        free(process);
                        waitpid(pid, NULL, WNOHANG);
                    } 
                }
            }
        }
        if(execvp(filenameLeader, argsLeader) == -1) exit(errno);

    }
    else free(processLeader); //in acsh
    return leader;
}