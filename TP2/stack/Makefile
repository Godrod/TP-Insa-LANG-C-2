CC=gcc
CFLAGS=-Wall
LDFLAGS=

main: stack.o test.o main.o
	$(CC) $^ -o $@

main.o: stack.h application.h
stack.o: stack.h test.h application.h
test.o: test.h 

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean: 
	rm -f *.o *~
	rm main
