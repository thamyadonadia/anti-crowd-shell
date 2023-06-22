acsh: main.o operation.o
	gcc -o acsh main.o operation.o


main.o: main.c operation.c
	gcc -o main.o main.c -c


operation.o: operation.c operation.h
	gcc -o operation.o operation.c -c 


clean:
	rm -rf *.o

run: acsh
	./acsh