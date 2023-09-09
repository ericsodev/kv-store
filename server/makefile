all: prog

prog: 
	gcc -o server server.o dict.o

server.o: server.c
	gcc -c server.c

dict.o: dict.c dict.h
	gcc -g -c dict.c

queue.o: queue.h queue.c
	gcc -c -g queue.c

testQueue.o: testQueue.c
	gcc -c -g testQueue.c

testDict.o: testDict.c dict.h
	gcc -c -g testDict.c

testDict: dict.o testDict.o
	gcc -g -o testDict testDict.o dict.o

testQueue: testQueue.o queue.o
	gcc -g -o testQueue testQueue.o queue.o

clean:
	rm -rf *.o
	rm testQueue testDict server
