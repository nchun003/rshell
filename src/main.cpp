#include <iostream>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <cstring>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <queue>


int exec(char **&argv)
{
	int errorcalled = 0;
	int pid = fork();
	if(pid == -1){
		perror("ERROR!");
		exit(1);
	}
	else if(pid == 0)			//Child process
	{
		if(execvp(argv[0], argv))
		{
			perror("execvp");
			errorcalled++;
			return errorcalled;
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
	return errorcalled;

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


void  findconnectors(char *token,int &i, char **&j, int &capacity, int &connector2)		//Checks if a token is a connector
{
	std::string sor = "||";
	char *orr = new char [sor.length()+1];
	strcpy(orr, sor.c_str());
	std::string sand = "&&";
	char *andd = new char [sand.length()+1];
	strcpy(andd, sand.c_str());
	std::string col = ";";
	char *coll = new char [col.length()+1];
	strcpy(coll, col.c_str());
	std::string comment = "#";
	char *comn = new char [comment.length()+1];	
	strcpy(comn, comment.c_str());
	std::string ext = "exit";
	std::string tokenstring = token;
	if((ext == tokenstring && connector2 == 3) || (ext == tokenstring && connector2 == 0))
	{
		exit(0);
	}
	if(ext == tokenstring && connector2 == 1)
	{
		exit(0);
	}
	if(connector2 == 5)
	{
		return;
	}
	if(*token == *comn)
	{
		exec(j);
		j = NULL;
		i = 0;
		connector2 = 5;
		return;
	}
	if(connector2 == 4)
	{
		return;
	}
	
	if(*token == *coll)									//If token is ; everything before it will get executed
	{
		connector2 = 1;
		exec(j);
		j = NULL;
		i = 0;
		return;
	}
	char *result = token;
	while((result = std::strstr(result, coll)) != NULL){					//Checks if token contains ';'
		strncpy(result, "\0", 2);
		if(connector2 == 2)
		{
			j = NULL;
			i = 0;
			connector2 = 0;
			return;
		}
		connector2 = 1;
		++result;
	}
	if(*token == *orr)									//Everything before || will get executed
	{
		if(connector2 == 2)
		{
			j = NULL;
			i = 0;
			return;
		}
		connector2 = 2;
		if(exec(j) == 1)
		{
			connector2 = 0;
			
		}
		j = NULL;
		i = 0;
		
		return;		
	} 
	else if(*token == *andd)
	{
		connector2 = 3; 
		if(exec(j) == 1)
		{
			connector2 = 4;
		}
		j = NULL;
		i = 0;
		return;
	}

	else{											//If token is not connector it will get put in j(argv)
		if(connector2 == 2)
		{
			return;
		}			
		++i;
		if(i >= capacity || i == 1)
		{
			expand(i, capacity, j);
		}
		int z = i-1;
		j[z] = token;
	}

	if(connector2 == 1)									//If ; connector was found, everything before is executed
	{
		exec(j);
		connector2 = 0;
		j = NULL;
		i = 0;
	}
}
	

void parsing(char *inpt)									//parses by using spaces
{
	int numarg = 0;
	int cap = 0;
	int connector = 0;
	char **args; 
	char *comm_1 = strtok(inpt, " ");
	while(comm_1 != NULL)
	{
		findconnectors(comm_1,numarg, args, cap, connector);
		comm_1 = strtok(NULL, " ");
	}
	if(connector == 2)									//If || dont execute right side
	{
		return;
	}
	if(exec(args) == 1)
	{
		exit(0);
	}
	return;
}

void userlogin()
{
	char *usrnme;
	char hostname[128];
	int hostnamework;
	if((usrnme = getlogin()) == NULL)
	{
		perror("getlogin() error");
	}
	hostnamework = gethostname(hostname, sizeof hostname);
	if(hostnamework == 0)
	{
		std::cout << usrnme << "@" << hostname;
	}
	else{
		perror("gethostname() error");
	}
}
		
int main(int argc, char **argv)
{
	std::string usrin;
	while(usrin != "exit")
	{
		userlogin();
		std::cout << "$ "; 			
		std::getline(std::cin,usrin);							//convert to cstring for parsing
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
