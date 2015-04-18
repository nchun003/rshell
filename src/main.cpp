#include <iostream>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <cstring>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <queue>

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

void expand(int &size2, int &cap2, char **&array)
{
	int i;
	if(size2 ==1)
	{
		cap2 = size2;
		cap2 = cap2*2;
		array = new char*[cap2];
		for(int n=0; n<cap2; n++)
		{
			array[n] = '\0';
		}
		return;
	}
	else{
		cap2 = cap2 *2;
		char **temp;
		temp = array;
		array = new char*[cap2];
		for(i =0; i<size2 ; ++i)
		{
			array[i] = temp[i];
		}
		for(int k = size2; k<cap2; k++)
		{
			array[k] = '\0';
		}
	}
}


void findconnectors(char *token,int &i, char **&j, int &capacity)		//Checks if a token is a connector
{
	int iscol = 0;
	std::string sor = "||";
	char *orr = new char [sor.length()+1];
	strcpy(orr, sor.c_str());
	std::string sand = "&&";
	char *andd = new char [sand.length()+1];
	strcpy(andd, sand.c_str());
	std::string col = ";";
	char *coll = new char [col.length()+1];
	strcpy(coll, col.c_str());

	char *result = token;
	while((result = std::strstr(result, coll)) != NULL){
//		std::cout << "Found " << coll << "starting at " << result << std::endl;
		strncpy(result, "\0", 2);
		iscol = 1;
		++result;
//		exec(j);
	}
//	exec(j);	

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
	else{
		++i;
		if(i >= capacity || i == 1)
		{
			expand(i, capacity, j);
		}
		int z = i-1;
		j[z] = token;
	}
	if(iscol == 1)
	{
		exec(j);
		i = 0;
	}
}
	

void parsing(char *inpt)			//parses by using spaces
{
	int numarg = 0;
	int cap = 0;
	char **args; 
        char *comm_1 = strtok(inpt, " ");
        while(comm_1 != NULL)
        {
		findconnectors(comm_1,numarg, args, cap);
		comm_1 = strtok(NULL, " ");
//		exec(args);
        }
	exec(args);
	return;
}


int main(int argc, char **argv)
{
	std::string usrin;
	while(usrin != "exit")
	{
		std::cout << "$ "; 			
		std::getline(std::cin,usrin);		//convert to cstring for parsing
		if(usrin == "exit")
		{
			exit(0);
		}
		char *cstr = new char [usrin.length()+1];
		std::strcpy (cstr, usrin.c_str());
		parsing(cstr);
	}
	return 0;	
}
