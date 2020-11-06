CC=gcc
CFLAGS=-Wall
LDFLAGS=

myhello: myhello.o mytools.o
	$(CC) $^ -o $@

myhello.o: mytools.h
mytools.o: mytools.h

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean: 
	rm -f *.o *~
	rm myhello
