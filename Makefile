CC=gcc
CFLAGS=  -Wall -Wextra -c -ggdb -pedantic -std=c99 -O0
LFLAGS=  -Wall -Wextra -pedantic  -std=c99 -ggdb

all: heapsort

stack.o:
	$(CC) $(CFLAGS) stack.c stack.h dll.c dll.h
queue.o:
	$(CC) $(CFLAGS) queue.c queue.h sll.c sll.h
scanner.o:
	$(CC) $(CFLAGS) scanner.c scanner.h
heap.o: stack.o queue.o
	$(CC) $(CFLAGS) heap.c heap.h
heapsort: heap.o
	$(CC) $(LFLAGS) heapsort.c heap.o stack.o queue.o -o heapsort

valgrind: heapsort
	@./valgrind heapsort

clean:
	@rm -f *.o
	@rm -f heapsort
	@rm -f *.gch
