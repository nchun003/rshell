CXX = g++
all:
	$(CXX) -Wall -Werror -ansi -pedantic -o rshell src/main.cpp

rshell:
	$(CXX) -Wall -Werror -ansi -pedantic -o rshell src/main.cpp


