CC=gcc
CFLAGS=-Wall -Wextra -g
LDFLAGS= 

all: main

main: main.o myDoubleTree.o
	$(CC) $^ $(LDFLAGS) -o $@


%.o: %.c
	$(CC) -c $(CFLAGS) $< -o $@
	
clean:
	rm -f *.o 
	rm -f main
