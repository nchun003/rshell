CC=g++
CFLAGS=-g -Wall -Werror -ansi -pedantic --std=c++11

<<<<<<< HEAD
all : rshell ls
=======
all : rshell cp
>>>>>>> 60fff5365f805a2c980965593394ad15dfd4ab01

rshell:
	mkdir -p bin
	$(CC) $(CFLAGS) src/main.cpp -o bin/rshell
<<<<<<< HEAD
	
ls:
	mkdir -p bin
	$(CC) $(CFLAGS) src/ls.cpp -o bin/ls
=======

cp:
	mkdir -p bin
	$(CC) $(CFLAGS) src/cp.cpp -o bin/cp
>>>>>>> 60fff5365f805a2c980965593394ad15dfd4ab01

