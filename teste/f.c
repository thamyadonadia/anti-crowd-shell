#include <stdio.h>
#include <unistd.h>

int main(int argc, char const *argv[]){
    printf("eu sou o processo=%d e estou rodando em foreground\n", getpid());
    return 0;
}
