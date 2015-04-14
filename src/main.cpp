#include <iostream>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <cstring>

void findconnectors(char *token)
{
	char *orr;
	std::strcpy(orr, "||");
	char *andd;
	std::strcpy(andd, "&&");
	char *col;
	std::strcpy(col, ";");
	if(token == orr)
	{
		std::cout<<"or" << std::endl;
	}
}
	


void parsing(char *inpt)			//parses by using spaces
{
        char *comm_1 = strtok(inpt, " ");
        while(comm_1 != NULL)
        {
                std::cout << comm_1 << std::endl;
		comm_1 = strtok(NULL, " ");
        }

}


int main(int argc, char **argv)
{
	std::cout << '$'; 			
	std::string usrin;			//reads in user input
	std::getline(std::cin,usrin);		//convert to cstring for parsing
	char *cstr = new char [usrin.length()+1];
	std::strcpy (cstr, usrin.c_str());
	parsing(cstr); 
	return 0;	
}
