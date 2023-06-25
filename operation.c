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
    int len = strlen(input);
    int k=0, inicio=0, processCount=0;
    pid_t leader; pid_t processGroupID;

    for(int i=0; i<= len; i++){
        if(((i != len-1) && (input[i] == '<' && input[i+1] == '3')) || input[i] == '\0'){
            if(input[i-1]==' ' || input[i]=='\0'){
                char* process = malloc(sizeof(char) * 100);
            
                for(int j=inicio; j<i; j++){
                    process[k] = input[j];
                    k++;
                }

                char* filename = strtok(process, " "); char* args[3]; int l=0;
                args[l] = strtok(NULL, " ");
                while(args[l] && l<2){
                    l++;
                    args[l] = strtok(NULL, " "); 
                }

                if(processCount==0){ // primeiro processo lido
                    leader = fork();

                    if(!leader){ // no filho
                        processGroupID = setsid();
                        execvp(filename, args);
                    } else waitpid(leader, NULL, WUNTRACED);

                }else{
                    pid_t pid = fork();

                    if(!pid){ // no filho
                        setpgid(pid, processGroupID);
                        execvp(filename, args);
                    } else waitpid(pid, NULL, WUNTRACED);
                }

                inicio = i+3; k=0; processCount++;
                free(process);
            }  
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