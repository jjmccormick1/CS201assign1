CC=clang
CFLAGS=  -Wall -Wextra  -c -ggdb -pedantic -std=c99 -O0
LFLAGS=  -Wall -Wextra  -pedantic  -std=c99 -ggdb

all: heapsort

dll.o: dll.c dll.h
	$(CC) $(CFLAGS) dll.c dll.h
sll.o: sll.c sll.h
	$(CC) $(CFLAGS) sll.c sll.h
stack.o: dll.o
	$(CC) $(CFLAGS) stack.c stack.h 
queue.o: sll.o
	$(CC) $(CFLAGS) queue.c queue.h 
scanner.o:
	$(CC) $(CFLAGS) scanner.c scanner.h
heap.o: stack.o queue.o
	$(CC) $(CFLAGS) heap.c heap.h
heapsort.o: 
	$(CC) $(CFLAGS) heapsort.c
heapsort: heap.o heapsort.o scanner.o
	$(CC) $(LFLAGS) heapsort.o heap.o stack.o dll.o queue.o sll.o scanner.o -o heapsort

valgrind: heapsort
	@./valgrind heapsort

clean:
	@rm -f *.o
	@rm -f heapsort
	@rm -f *.gch
