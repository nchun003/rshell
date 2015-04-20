CC=g++
CFLAGS=-g -Wall -Werror -ansi -pedantic --std=c++11

all : rshell

rshell:
	mkdir -p bin
	$(CC) $(CFLAGS) src/main.cpp -o bin/rshell


