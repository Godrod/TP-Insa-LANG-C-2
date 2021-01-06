CC=gcc
CFLAGS=-Wall -Wextra -g
CFLAGS+= -DTEST_UNIT -DMY_USE_LIST
LDFLAGS= 

all: main_testMO

main_testlist: listMO.o main_testlist.o multimedia-object.o test.o
main_testMO: main_testMO.o multimedia-object.o test.o
mo_console: main_console1.o listMO.o multimedia-object.o managerMO-list.o test.o
main_gtk: CFLAGS+= -DMY_USE_LIST
main_gtk: CFLAGS+= `pkg-config --cflags gtk+-3.0`
main_gtk: LDFLAGS+= `pkg-config --libs gtk+-3.0`
main_gtk: main_gtk.o multimedia-object.o listMO.o managerMO-list.o test.o fichier.o callback-functions-managerMO.o IOFileManagerMO.o
	$(CC) $^ $(LDFLAGS) -o $@

	$(CC) $^ $(LDFLAGS) -o $@

%.o: %.c
	$(CC) -c $(CFLAGS) $< -o $@
	
clean:
	rm -f *.o 
	rm -f main_testMO mo_console main_gtk
