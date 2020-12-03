CC=gcc
CFLAGS=-Wall
LDFLAGS=

main: stack.o evaluation.o main.o test.o evaluationFromString.o
	$(CC) $^ -o $@

main.o: stack.h application.h
stack.o: stack.h evaluation.h application.h
evaluation.o: evaluation.h
test.o: test.h
evaluationFromString.c: 

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean: 
	rm -f *.o *~
	rm main
