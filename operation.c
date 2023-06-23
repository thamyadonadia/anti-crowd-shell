#include "operation.h"
#include "services.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>

// ========== Operações Internas ============
void changeDirectory(char* path, char* cwd){
    chdir(path);
    getcwd(cwd, 1000);
}

void exitShell(char* input, int* sessionLeaders, int* countLeaders){
    for(int i=0; i<(*countLeaders); i++){
        kill(sessionLeaders[i], SIGKILL);
    }

    free(sessionLeaders); free(input);
    exit(0);
}


// =========== Execução de programas ==========
void singleProcess(char* command){ // recebe o comando sem o %
    // nome do executável + no máximo 3 argumentos
    char* filename; char* args[3]; int i=0;
    pid_t pid;
    //processo em foreground
    if(checkDelimiter(command)){
        pid = fork();
        //no filho
        if(!pid){
            filename = strtok(command, " ");

            printf("filename: %s\n", filename);

            while(args[i] && i<2){
                args[i] = strtok(NULL, " "); 
                printf("arg[%d] = %s\n", i, args[i]);
            }

            execvp(filename, args); // no filho
        }
        else waitpid(pid, NULL, WUNTRACED); //no pai
    }
    //processo em background
    else{
        pid = fork();
        //no filho
        if(!pid){
            filename = strtok(command, " ");

            printf("filename: %s\n", filename);

            while(args[i] && i<2){
                args[i] = strtok(NULL, " "); 
                printf("arg[%d] = %s\n", i, args[i]);
            }
            setsid();
            execvp(filename, args); // no filho
        }
    }
}

int backgroundGroupProcess(char* input){
    int len = strlen(input);
    int processCount=1; 
    pid_t leader; pid_t processGroupID;

    for(int i=0; i<len; i++){
        //possivel delimitador encontrado
        if(input[i]=='<' && input[i+1]=='3'){
            //confirmação da delimitação e que há outro programa a ser executado
            if(input[i-1]== ' ' && input[i+2]== ' ') processCount++;
        }
    }

    printf("number of process = %d\n", processCount);

    /*for(int j=0; j<processCount; j++){
        char* filename = strtok(input, " "); char* args[3]; int i=0;

        while(args[i] && i<2){
            args[i] = strtok(NULL, " "); 
        }
        
        if(j==0){ 
            leader = fork();

            if(!leader){
                processGroupID = setsid();
                execvp(filename, args);
            }
            
        }else{
            pid_t pid = fork();

            if(!pid){
                setpgid(pid, processGroupID);
                execvp(filename, args);
            }
        }

    }*/

    return leader;
}

void list(char* args){
    int pid = fork();
    int status;
    if(!pid){
        execv("/bin/ls", &args);
        exit(0);
    }
    else{
        waitpid(pid, &status, 0);
    }
}