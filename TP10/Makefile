CC=gcc
CFLAGS=-Wall -Wextra -g
LDFLAGS= 
OBJECTS_TO_CLEAN = main.o \
		  		   image.o \
		  		   huffman.o
all: main

main: main.o image.o huffman.o list_teacher.o huffman_method_teacher.o
	$(CC) $^ $(LDFLAGS) -o $@


%.o: %.c
	$(CC) -c $(CFLAGS) $< -o $@
	
clean:
	rm -f $(OBJECTS_TO_CLEAN)
	rm -f main
