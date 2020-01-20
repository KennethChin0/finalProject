all: main.o function.o
	gcc -o program main.o function.o

main.o: main.c function.h
	gcc -c main.c function.h

function.o: function.c function.h
	gcc -c function.c function.h

run:
		./program


clean:
		rm *.o
		rm program
