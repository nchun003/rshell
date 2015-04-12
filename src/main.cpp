#include <iostream>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <cstring>

int main(int argc, char **argv)
{
	std::cout << '$'; 			
	std::string usrin;			//reads in user input
	std::getline(std::cin,usrin);		//convert to cstring for parsing
	char *cstr = new char [usrin.length()+1];
	std::strcpy (cstr, usrin.c_str());
	char *comm_1 = strtok(cstr, "||");
	while(comm_1 != NULL)
	{
		std::cout << comm_1 << std::endl;
		comm_1 = strtok(NULL, "||");
	}
	char *comm_2 = strtok(cstr, "&&");
	while(comm_2 != NULL)
	{
		std::cout << comm_2 << std::endl;
		comm_2 = strtok(NULL, "&&");
	}
	char *comm_3 = strtok(cstr, ";");
	while(comm_3 != NULL)
	{
		std::cout << comm_3 << std::endl;
		comm_3 = strtok(NULL, ";");
	}


	return 0;	
}
