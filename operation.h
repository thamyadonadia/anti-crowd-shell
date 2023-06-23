#ifndef OPERATION_H
#define OPERATION_H

/** Altera o diretório corrente do shell
 * @param char* caminho do diretório destino
 * @param char* diretório atual do shell
*/
void changeDirectory(char* path, char* cwd);

//must free everything
void exitShell(char* input, int* sessionLeaders, int* countLeaders);

/** Executa um comando em foreground
 * @param char* comando a ser executado em foreground, sem o operador especial
*/
void singleProcess(char* command);

/** Executa até 5 comandos em background
 * @param char* input passado na linha de comando
 * @return int id do processo líder da sessão
*/
int backgroundGroupProcess(char* input);

void list(char* args);

#endif