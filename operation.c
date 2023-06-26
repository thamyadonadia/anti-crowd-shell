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
        printf("%d\n", i);
    }

    free(sessionLeaders); free(input);
    exit(0);
}


// =========== Execução de programas ==========
void singleProcess(char* command){ // recebe o comando sem o %
    // nome do executável + no máximo 3 argumentos
    printf("UNICO PROCESSO\n");
    
    char* filename; 

    //TODO: ADAPTAR ESSA PARTE DO CÓDIGO7
    char* args[5] = {NULL, NULL, NULL, NULL, NULL}; 
    int i=0; pid_t pid;
    
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
            //TODO: THAMYA SABE O QUE É
            setsid();
            execvp(filename, args); 
        }
        waitpid(pid, NULL, WUNTRACED);
    }
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
    pid_t leader = fork();
    pid_t pid;
    if(leader == 0){ // no processo filho líder
       setsid(); //processo em nova sessão

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
                    //printf("%s %s %s %s %s\n", args[0], args[1], args[2], args[3] ,args[4]);
                    pid = fork();
                    if(pid==0) execvp(filename, args);
                    else{
                        free(process);
                        waitpid(pid, NULL, WNOHANG);
                    } 
                }
            }
        }
        execvp(filenameLeader, argsLeader);

    } else{
        free(processLeader);
        waitpid(leader, NULL, WNOHANG);
        sleep(1);
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