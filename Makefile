CFLAGS = -g -Wall
CC = gcc
all: main

main: main.o fonts.o

start: main
	./main

clean:
	rm -f main *.o

.PHONY: clean