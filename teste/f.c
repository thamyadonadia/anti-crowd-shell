#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char const *argv[]){
    printf("eu sou o processo=%d e estou rodando\n", getpid());
    sleep(30);
    exit(0);
}
