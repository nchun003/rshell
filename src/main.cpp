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
	std::string command;
	char **arg_list;
	int size = 0; 
	int cap = 0; 
	char *comm_1 = strtok(cstr, " ");
        while(comm_1 != NULL)
        {
		if (comm_1=="||") {}
		else if (comm_1=="&&") {}
		else if (comm_1 == ";"){}
		command=comm_1;
		while(
                std::cout << comm_1 << std::endl;
                comm_1 = strtok(NULL, " ");
        }

	return 0;	
}
