#include <iostream>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <cstring>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>


void exec(char **argv)
{
	int pid = fork();
	if(pid == -1){
		perror("ERROR!");
		exit(1);
	}
	else if(pid == 0)			//Child process
	{
		std::cout << "Child Process";
		if(execvp(argv[0], argv))
		{
			perror("No error.");
		}
		exit(1);			//Child killed when done with task
	}
	else if(pid > 0)
	{
		if(wait(0) == -1)		//Waits for child process to finish
		{
			perror("Wait error!");
		}
	}

}

void findconnectors(char *token)		//Checks if a token is a connector
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
		std::cout << "OR!" << std::endl;	
	} 
	else if(*token == *andd)
	{
		std::cout << "AND!" << std::endl;
	}
	else if(*token == *coll)
	{
		std::cout << "COLON!" << std::endl;
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
