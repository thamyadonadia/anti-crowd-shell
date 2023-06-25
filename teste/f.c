#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char const *argv[]){
    printf("eu sou o processo=%d e estou rodando em foreground\n", getpid());
    sleep(300000000);
    exit(0);
}
