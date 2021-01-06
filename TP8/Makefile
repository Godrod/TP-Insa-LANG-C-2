CC=gcc
CFLAGS=-Wall -Wextra -g
CFLAGS+= -DTEST_UNIT -DMY_USE_LIST
LDFLAGS= 

all: main

main: main.o test.o myAlloc.o myFunctions.o fichier.o memoryList.o
	$(CC) $^ $(LDFLAGS) -o $@

main_testlist: main_testlist.o test.o fichier.o memoryList.o
	$(CC) $^ $(LDFLAGS) -o $@

%.o: %.c
	$(CC) -c $(CFLAGS) $< -o $@
	
clean:
	rm -f *.o 
	rm -f main_testlist main
