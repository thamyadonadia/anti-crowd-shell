acsh: main.o operation.o services.o
	@gcc -o acsh main.o operation.o services.o


main.o: main.c operation.h services.h
	@gcc -o main.o main.c -c


operation.o: operation.c operation.h
	@gcc -o operation.o operation.c -c 

services.o: services.c services.h
	@gcc -o services.o services.c -c

clean:
	@rm -rf *.o

run: acsh
	@./acsh

val: acsh
	@valgrind ./acsh