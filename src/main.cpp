#include <iostream>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <cstring>

void findconnectors(char *token)
{
	std::string sor = "||";
	char *orr = new char [sor.length()+1];
	strcpy(orr, sor.c_str());
	std::string sand = "&&";
	char *andd = new char [sand.length()+1];
	strcpy(andd, sand.c_str());
	std::string col = ";";
	char *coll = new char [col.length()+1];
	std::cout << "token:" << token << " or:" << orr << std::endl;
	if(*token == *orr)
	{
		
	} 
	else if(*token == *andd)
	{
	}
	else if(*token == *coll)
	{
	}

}
	


void parsing(char *inpt)			//parses by using spaces
{
        char *comm_1 = strtok(inpt, " ");
        while(comm_1 != NULL)
        {
                std::cout << comm_1 << std::endl;
		findconnectors(comm_1);
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
