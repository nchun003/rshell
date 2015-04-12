#include <iostream>
#include <string.h>
#include <stdio.h>
#include <unistd.h>

int main(int argc, char **argv)
{
	std::cout << '$';
	std::string usrin; 
	std::getline(std::cin,usrin);
	
	return 0;	
}
