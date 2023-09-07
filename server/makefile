all: prog

prog: 
	gcc -o server server.o dict.o

server.o: server.c
	gcc -c server.c

dict.o: dict.c dict.h
	gcc -g -c dict.c

testDict.o: testDict.c dict.h
	gcc -c -g testDict.c

testDict: dict.o testDict.o
	gcc -g -o testDict testDict.o dict.o

clean:
	rm -rf *.o
