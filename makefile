all : strassen

strassen : strassen.o
	gcc -std=c99 -o strassen strassen.o 

strassen.o : strassen.c
	gcc -std=c99 -c strassen.c

clean :
	rm strassen *.o