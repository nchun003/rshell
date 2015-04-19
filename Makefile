CC=g++
all:
	bin rshell ls cp

rshell:
	$(CC) -Wall -Werror -ansi -pedantic -o rshell src/main.cpp -o bin/rshell


