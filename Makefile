EXEC = main
CC = gcc
CFLAGS = -Wall -Werror -pedantic -std=c99 -g
BIN = $(filter-out $(EXEC).c, $(wildcard *.c))
BINFILES = $(BIN:.c=.o)
TESTSCRIPT = pruebas.sh

all: main

%.o: %.c %.h
	$(CC) $(CFLAGS) -c $<
	
main: $(BINFILES)  $(EXEC).c
	$(CC) $(CFLAGS) $(BINFILES) $(EXEC).c -o $(EXEC)

clean:
	rm -f $(wildcard *.o) $(EXEC) *.pgm -r imagenes/

pruebas: $(EXEC)
	mkdir imagenes
	bash $(TESTSCRIPT)
	mv *.pgm imagenes/

.PHONY: clean main
