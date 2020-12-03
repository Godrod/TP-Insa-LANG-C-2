CC = gcc
CFLAGS = -Wall
DEBUG = 1

ifeq ($(DEBUG),1)
	CFLAGS += -g
endif

OBJS = main.o image.o BMPFile.o
LIBS = BMPFile_teacher.o fichier_teacher.o

all: main

main: $(OBJS) $(LIBS)
main.o: image.h
image.o: image.h
BMPFile.o: BMPFile.h

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJS) main