all: accountFunctions.o transactions.o screen.o
	gcc accountFunctions.o transactions.o screen.o main.c -o app

screen.o: screen.h
	gcc -c screen.c

accountFunctions.o: accountFunctions.h
	gcc -c accountFunctions.c

transactions.o: transactions.h
	gcc -c transactions.c

clean:
	rm -rf *.o