#include "operation.h"
#include "services.h"
#include "signalhandler.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>
#include <fcntl.h>

// ========== Operações Internas ============
void changeDirectory(char* path){
    if(path == NULL) chdir("/");
    if((chdir(path) == -1) && (errno == ENOENT)) printf("ERROR: Directory or file not found!\n");
}

void exitShell(char* input, int* sessionLeaders, int* countLeaders){
    for(int i=0; i<(*countLeaders); i++){
        kill(sessionLeaders[i]*(-1), SIGKILL);
    }
    free(sessionLeaders);
    free(input);
    exit(0);
}

// =========== Execução de programas ==========
//TODO: PERGUNTAR AO ZE GONC SOBRE A QUESTAO DO %
//SE É EXCLUSIVO OU SE PODE SER USADO COMO PARTE DO NOME DE PROGRAMA
void foreGroundSingleProcess(char* command){
    char* filename; int i=0; pid_t pid;
    char* args[5] = {NULL, NULL, NULL, NULL, NULL}; 

    pid = fork();
    if(!pid){ //no filho
        filename = strtok(command, " ");
        while(args[i] && i<2){
            args[i] = strtok(NULL, " "); i++; // TODO: tirar o % dos argumentos
        }
        //EXEC_DEFAULT()
        signalExecDefault();
        execvp(filename, args);
    }

    else {
        //EXEC_RUNNING()
        signalExecRunning();
        waitpid(pid, NULL, WUNTRACED); //no pai
        //EXEC_FINISHED()
        signalExecFinished();
    }
}

int backGroundSingleProcess(char* command){
    char* filename; int i=1; pid_t pid;
    char* args[5] = {NULL, NULL, NULL, NULL, NULL}; 
    pid = fork();

    if(!pid){ //no filho
        filename = strtok(command, " ");
        args[0] = filename;

        while(args[i] && i<3){
            args[i] = strtok(NULL, " "); 
        }
        setsid();

        int devNull = open("/dev/null", O_RDWR);
        dup2(devNull, STDIN_FILENO);
        dup2(devNull, STDOUT_FILENO);
        close(devNull);

        if(execvp(filename, args) == -1) exit(errno);

    }
    
    return pid;
}


int backgroundGroupProcess(char* input){
    int len = strlen(input);
    int k=0, inicio=0;

    char* processLeader = malloc(sizeof(char) * strlen(input)); char* filenameLeader; 
    char* argsLeader[5] = {NULL, NULL, NULL, NULL, NULL};
            
    // pega o processo líder
    for(int i=0; i<= len; i++){
        if(((i != len-1) && (input[i] == '<' && input[i+1] == '3')) || input[i] == '\0'){
            if(input[i-1]==' ' || input[i]=='\0'){
               
                for(int j=inicio; j<i; j++){
                    processLeader[k] = input[j];
                    k++;
                }

                filenameLeader = strtok(processLeader, " "); int l=0;
                argsLeader[0] = filenameLeader;
                argsLeader[l] = strtok(NULL, " ");

                while(argsLeader[l] && l<3){
                    l++;
                    argsLeader[l] = strtok(NULL, " "); 
                }

                inicio = i+3; k=0; 
                break;
            }
        }
    }

    pid_t leader = fork(); pid_t pid;
    if(leader == 0){ // no processo filho líder
       setsid(); //processo em nova sessão

        int devNull = open("/dev/null", O_RDWR);
        dup2(devNull, STDIN_FILENO);
        dup2(devNull, STDOUT_FILENO);
        close(devNull);

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

    }else{
        free(processLeader);
    }
    return leader;
}