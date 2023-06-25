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
    chdir(path); //TODO: verificação de erro caso o diretório não exista.
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
    printf("UNICO PROCESSO\n");
    
    char* filename; char* args[3]; int i=0; pid_t pid;
    
    if(checkForeground(command)){
        pid = fork();
        
        if(!pid){ //no filho
            filename = strtok(command, " ");

            while(args[i] && i<2){
                args[i] = strtok(NULL, " "); i++; // TODO: tirar o % dos argumentos
                printf("arg[%d] = %s\n", i, args[i]);
            }
            execvp(filename, args);
        }

        else waitpid(pid, NULL, WUNTRACED); //no pai
    }
    //processo em background
    else{
        printf("PROCESSO BACKGROUND\n");
        pid = fork();

        if(!pid){ //no filho
            filename = strtok(command, " ");

            while(args[i] && i<2){
                args[i] = strtok(NULL, " "); 
                //printf("arg[%d] = %s\n", i, args[i]);
            }
            
            setsid();
            execvp(filename, args); 
        }
        waitpid(pid, NULL, WUNTRACED);
    }
}

int backgroundGroupProcess(char* input){
    int len = strlen(input); int j=0;
    int processCount=1; int delimPosition[4];
    pid_t leader; pid_t processGroupID;

    for(int i=0; i<len; i++){
        //possivel delimitador encontrado
        if(input[i]=='<' && input[i+1]=='3'){
            //confirmação da delimitação e que há outro programa a ser executado
            if(input[i-1]== ' ' && input[i+2]== ' '){
                processCount++;
            } 
        }
    }

    // f 1 2 3 <3 t1 1 2 3 i=8 delimPosition[0]=8
    // strtok(input, "<3")

    printf("number of process = %d\n", processCount);

    for(int j=0; j<processCount; j++){       
        if(j==0){ 
            char* filename = strtok(input, "<3"); char* args[3]; int i=0;
            printf("process filename: %s\n", filename);

            printf("args program=%s : ", filename);
            while(args[i] && i<2){
                args[i] = strtok(NULL, " ");
                printf("%s ", args[i]);
                i++;
            }
        
           // leader = fork();

           /* if(!leader){
                processGroupID = setsid();
                execvp(filename, args);
            }
            else printf("session leader pid=%d\n", leader);*/
            
        }else{
            char* filename = strtok(NULL, "<3"); char* args[3]; int i=0;
            printf("process filename: %s\n", filename);

            printf("args program=%s : ", filename);
            while(args[i] && i<2){
                args[i] = strtok(NULL, " ");
                printf("%s ", args[i]);
                i++;
            }
            /*pid_t pid = fork();

            if(!pid){
                setpgid(pid, processGroupID);
                execvp(filename, args);
            }
            else printf("process in background pid=%d\n", pid);*/
        }
    }

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