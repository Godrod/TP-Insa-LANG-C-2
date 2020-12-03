CC=gcc
CFLAGS=-Wall -Wextra -g
LDFLAGS= 

all: main_testlist

main_testlist: listMO.o main_testlist.o multimedia-object.o test.o
main_testMO: CFLAGS+= -DTEST_UNIT
main_testMO: main_testMO.o multimedia-object.o test.o
	$(CC) $^ $(LDFLAGS) -o $@

%.o: %.c
	$(CC) -c $(CFLAGS) $< -o $@
	
clean:
	rm -f *.o 
	rm -f main_testMO
