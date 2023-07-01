#MAKEFILE By: Afonso Salvador de Magalhaes
#With support of Kevin Carvalho de Jesus and João Paulo Moura

NAME_PROGRAM = prog
CC = gcc
FLAGS = -lm -pedantic -Wall 
C_FILES = $(wildcard *.c)
O_FILES = $(patsubst %.c, %.o, $(C_FILES))

all: $(O_FILES) create_executable

CYAN = "\033[1;36m"
YELLOW = "\033[1;33m"
WHITE = "\033[1;37m"
RED = "\033[1;31m"
RESET = "\033[0m"


main.o: main.c
	@ echo $(CYAN)
	@ echo "Compilando main.c ..."
	@ $(CC) -c $< $(FLAGS)
	@ echo $(RESET)

%.o: %.c %.h
	@ echo $(CYAN)
	@ echo "Compilando $< ..."
	@ $(CC) -c $< $(FLAGS)
	@ echo $(RESET)

create_executable: 
	@ echo $(CYAN)
	@ echo "Criando executavel..."
	@ $(CC) -o $(NAME_PROGRAM) $(O_FILES) $(FLAGS)
	@ echo $(RESET)

run: 
	@ echo $(CYAN)
	@ echo "Executando programa ..."
	@ echo $(RESET)
	@ ./$(NAME_PROGRAM)

test: clean all run

valgrind: 
	@ echo $(YELLOW)
	@ echo "Rodando valgrind ..."
	@ echo $(RESET)
	@ valgrind ./$(NAME_PROGRAM)

clean: 
	@ echo $(WHITE)
	@ echo "Limpando arquivos temporarios ..."
	@ rm -rf $(NAME_PROGRAM) $(O_FILES)
	@ echo $(RESET)

clean_test:
	@ echo $(RED)
	@ echo "Removendo arquivos gerais ..."
	@ rm -rf $(NAME_PROGRAM) $(O_FILES) *.txt
	@ echo $(RESET)

rerun: clean all print run
	
print:
	@ echo $(YELLOW) && clear
	@ echo "Atualizando executavel e rodando ..."
	@ echo $(RESET)