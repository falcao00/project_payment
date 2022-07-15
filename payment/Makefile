all: accountFunctions.o transactions.o
	gcc accountFunctions.o transactions.o main.c -o app

accountFunctions.o: accountFunctions.h
	gcc -c accountFunctions.c

transactions.o: transactions.h
	gcc -c transactions.c

clean:
	rm -rf *.o