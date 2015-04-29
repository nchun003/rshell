CC=g++
CFLAGS=-g -Wall -Werror -ansi -pedantic --std=c++11

all : rshell cp

rshell:
	mkdir -p bin
	$(CC) $(CFLAGS) src/main.cpp -o bin/rshell

cp:
	mkdir -p bin
	$(CC) $(CFLAGS) src/cp.cpp -o bin/cp

