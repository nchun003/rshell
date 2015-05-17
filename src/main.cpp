#include <iostream>
#include <string>
#include <vector>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <cstring>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <queue>
#include <fcntl.h>
#include <fstream>

int errorcalled;
//int out = 0;
//int connector = 0;

void exec(char **&argv)
{
	errorcalled = 0;
	int pid = fork();
	if(pid == -1){
		perror("ERROR!");
		exit(1);
	}
	else if(pid == 0)			//Child process
	{
//		std::cout << "Child Process";
		if(-1 == execvp(argv[0], argv))
		{
			perror("execvp");
			errorcalled++;
	//		return errorcalled;
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
	//return errorcalled;
	return;
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

/*void redirection(char **file)
{
//	int savestdin = dup(0);
//	if(-1 == savestdin){
//		perror("Error with dup.");
//	}
//	else{
//		const char *file2 = file;
//		int f = open("src/bla", O_RDONLY);
//		int f = open("bla", std::fstream::in | std::fstream::out | std::fstream::app);
//		int fdup = dup2(f,0);
//		close(f);
//		if(-1 == fdup)
//			perror("Error with dup2.");
//	}
//	std::string instr("bla");
//	char *infile = new char[instr.length()+1];
//	strcpy(infile, instr.c_str());

	//char *grep[] = {infile};

	int in = open("bla", O_RDONLY);
	//dup2(in, 0);
	//close(in);
	execvp("cat", file);	

	return;
} */

std::vector<char *> tokens;
std::vector<char **> tokens2(200);
int x = 0;
void  findconnectors(char *token,int &i, char **&j, int &capacity, int &connector2)		//Checks if a token is a connector
{
	//std::vector<char *> tokens;
	tokens.push_back(token);	
	std::string tokenS(token);

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
	std::string in = "<";
	char *inn = new char [in.length()+1];
	strcpy(inn, in.c_str());
	std::string p = "|";
	char *p2 = new char [p.length()+1];
	strcpy(p2, p.c_str());
//	std::string out2 = ">>";
//	char *outt2 = new char [out2.length()+1];
//	strcpy(outt2, out2.c_str());

	std::string out1 = ">";
	char *outt = new char [out1.length()+1];
	strcpy(outt, out1.c_str());
	
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
/*	if(connector2 == 8)
	{
		int saveout;
		if(-1 == (saveout = dup(1)))
		{
			perror("Error with dup. ");
		}
		if(connector2 == 8)
		{
			if(-1 == (dup2(out, 1)))
			{
				perror("Error with dup2. ");
			}
			close(out);
		}
		std::cout << "hi";	
	}*/
	
	if(connector2 == 6)// || connector2 == 8)				//If input
	{
		//int saveout;
		//if(-1 == (saveout = dup(1)))
		//{
		//	perror("Error with dup. ");
		//}
//		char **b = &token;
//		char *b[] = {token, NULL};
/*		if(connector2 == 8)
		{
			if(-1 == (dup2(out, 1)))
			{
				perror("Error with dup2.");
			}
			close(out);
		}
*/
		j[1] = token;
		j[2] = NULL;
		int pid = fork();
		if(pid == -1){
			perror("ERROR!");
			exit(1);
		}
		else if(pid == 0)			//Child process
		{
			if(-1 == execvp(j[0], j))//tokens[0], b))//tokens[0], b))
			{
				perror("Error execvp.");
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
	//	if(-1 == (dup2(saveout, 1)))
	//	{
	//		perror("Error with dup2. ");
	//	}
		
		return;
	}
	
	if(connector2 == 9)
	{	int saveout;
		if(-1 == (saveout = dup(1)))
		{
			perror("Error with dup. ");
		}
		const char *b = token;
		int o = open(b, O_WRONLY |O_APPEND | O_CREAT, S_IRUSR | S_IRGRP | S_IWGRP | S_IWUSR);
		if(o == -1)
		{
			perror("Error with open. ");
		}
		if(-1 == (dup2(o, 1)))
		{
			perror("Error with dup2. ");
		}
		if(-1 == close(o))
		{
			perror("Error with close. ");
		}	
		int pid = fork();
		if(pid == -1){
			perror("ERROR!");
			exit(1);
		}
		else if(pid == 0)			//Child process
		{
			if(-1 == execvp(j[0], j))
			{
				perror("Error execvp.");
			}
			exit(1);			//Child killed when done with task
		}
		else if(pid > 0)
		{
			
			if(wait(0) == -1)		//Waits for child process to finish
			{
				perror("Wait error!");
			}
			if(-1 == (dup2(saveout, 1)))
			{
				perror("Error with dup2. ");
			}	
			if(-1 == close(saveout))
			{
				perror("Error with close. ");
			}
		}

		/*int saveout;
		if(-1 == (saveout = dup(1)))
		{
			perror("Error with dup.");
		}
		const char *b = token;
		int o = open(b, O_WRONLY |O_APPEND | O_CREAT, S_IRUSR | S_IRGRP | S_IWGRP | S_IWUSR);
		if(-1 == (dup2(o, 1)))
		{
			perror("Error with dup2. ");
		}
		close(o);	
		exec(j);
		if(-1 == (dup2(saveout, 1)))
		{
			perror("Error with dup2. ");
		}*/
		return;
	}

	if(connector2 == 7)				//If output
	{
		int saveout;
		if(-1 == (saveout = dup(1)))
		{
			perror("Error with dup. ");
		}
		const char *b = token;
		int o = open(b, O_WRONLY |O_TRUNC | O_CREAT, S_IRUSR | S_IRGRP | S_IWGRP | S_IWUSR);
		if(o == -1)
		{
			perror("Error with open. ");
		}
		if(-1 == (dup2(o, 1)))
		{
			perror("Error with dup2. ");
		}
		if(-1 == close(o))
		{
			perror("Error with close. ");
		}
		int pid = fork();
		if(pid == -1){
			perror("ERROR!");
			exit(1);
		}
		else if(pid == 0)			//Child process
		{
			if(-1 == execvp(j[0], j))
			{
				perror("Error execvp.");
			}
			exit(1);			//Child killed when done with task
		}
		else if(pid > 0)
		{
			
			if(wait(0) == -1)		//Waits for child process to finish
			{
				perror("Wait error!");
			}
			if(-1 == (dup2(saveout, 1)))
			{
				perror("Error with dup2. ");
			}	
			if(-1 == close(saveout))
			{
				perror("Error with close. ");
			}
		}
		/*int saveout;
		if(-1 == (saveout = dup(1)))
		{
			perror("Error with dup.");
		}
		const char *b = token;
		int o = open(b, O_WRONLY |O_TRUNC | O_CREAT, S_IRUSR | S_IRGRP | S_IWGRP | S_IWUSR);
		if(-1 == (dup2(o, 1)))
		{
		}
		close(o);	
		exec(j);
		if(-1 == (dup2(saveout, 1)))
		{
			perror("Error with dup2. ");
		}*/
		return;
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
	if(connector2 == 4)									//&& failed
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
//		std::cout << "Found " << coll << "starting at " << result << std::endl;
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
	if(std::string::npos != tokenS.find("||"))//*token == *orr)									//Everything before || will get executed
	{
		if(connector2 == 2)								//If or command already succeeded, leave
		{
			j = NULL;
			i = 0;
			return;
		}
		connector2 = 2;
		exec(j);
		if(errorcalled == 1)								//If or failed try next command
		{
			connector2 = 0;
			
		}
		j = NULL;
		i = 0;
		
		return;		
	} 
	if(*token == *p2)
	{
		connector2 = 10;
		tokens2[x] = j;
		x++;
		j = NULL;
		i = 0;
		//int z = i-1;
		//j[z] = NULL;
		return;
	}

	else if(*token == *andd)
	{
		connector2 = 3;
		exec(j); 
		if(errorcalled == 1)
		{
			connector2 = 4;
		}
	//	j = NULL;
		i = 0;
		return;
	}
	else if(*token == *inn)
	{
	//	int fd[2];
	//	pipe(fd);
	//	dup(fd[0]);
		/*if(connector2 == 8)
		{}
		else{*/
			connector2 = 6;
	//	}	
//		j = NULL;
//		i = 0; 
		//redirection(j);
	//	exec(j);
	//	return;
	}
	else if(std::string::npos != tokenS.find(">>"))
	{
		connector2 = 9;
	}
//	else if(*token == *outt2)
//	{
//		std::cout << "double out";
//	}
	else if(*token == *outt)
	{
	//	if(connector2 == 8)
	//	{
	//		return;
	//	}
	//	else{
			connector2 = 7;
	//	}
//		j = NULL;
//		i = 0;
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
		//std::cout << z;
		j[z] = token;
		//if(connector2 == 10)
		//{
		//	std::cout << "bye";
		//	tokens2[x] = j;
		//	x++;
		//	connector2 = 11;
		//}
		//if(tokens2[0] == NULL)
		//{
		//	std::cout << "tokens2 null";
		//}
		//std::cout << "hi" << token;
	}
/*	if(connector2 == 11)
	{
		std::cout << "hi2";
		//char *a = {"sort", "-r", NULL};
		//const char *b[] = {"sort", "-r", NULL};
		//char *b = new char[3];
		//char **a;
		//strcpy(*a, &b);
		//char **a = &b;
		//char *a = "hi";
		//char *const b[] = {a};
		int pid;
		int pipefd[2];
		if(-1 == pipe(pipefd))
		{
			perror("Error pipe. ");
		}
		pid = fork();
		if(pid == -1)
		{
			perror("Fork error. ");
		}
		else if(pid == 0)
		{
			
			if(-1 == dup2(pipefd[0], 0))
			{
				perror("Error dup2.");
			}
			if(-1 == close(pipefd[1]))
			{
				perror("Error close. ");
			}
			if(-1 == execvp(tokens2[1][0], tokens2[1]))
			{
				perror("Error execvp. ");
			}
		}
		else if(pid > 0)
		{
			//if(wait(0) == -1)
			//{
			//	perror("Wait error. ");
			//}
			if(-1 == dup2(pipefd[1], 1))
			{
				perror("Error dup2. ");
			}
			if(-1 == close(pipefd[0]))
			{
				perror("Error close. ");
			}
			if(-1 == execvp(tokens2[0][0], tokens2[0]))
			{
				perror("Error execvp. ");
			}
		}
		return;
	}	
*/	if(connector2 == 1)									//If ; connector was found, everything before is executed
	{
		exec(j);
		connector2 = 0;
		j = NULL;
		i = 0;
	}
}
	
/*void preparse(char *inpt)
{
	std::cout << "preparse called";
	char *comm_1 = strtok(inpt, " ");
	while(comm_1 != NULL)
	{
		std::string out1 = ">";
		char *outt = new char [out1.length()+1];
		strcpy(outt, out1.c_str());
		if(connector == 7)				//If output
		{
			int saveout;
			if(-1 == (saveout = dup(1)))
			{
				perror("Error with dup.");
			}
			const char *b = comm_1 ;
			out = open(b, O_WRONLY | O_TRUNC | O_CREAT, S_IRUSR | S_IRGRP | S_IWGRP | S_IWUSR);	
			if(out == -1)
			{
				perror("Open error. ");
			}
		//	if(-1 == (dup2(out, 1)))
		//	{
		//		perror("Error with dup2. ");
		//	}
			connector = 8;
		//	close(out);	
		//	if(-1 == (dup2(saveout, 1)))
		//	{
		//		perror("Error with dup2. ");
		//	}
			return;
		}
		if(*comm_1 == *outt)
		{
			connector = 7;
		}
		comm_1 = strtok(NULL, " ");
	}
	return;
}*/
	
void parsing(char *inpt)									//parses by using spaces
{
//	std::cout << "parsing called";
//	int out = 0;
	int numarg = 0;
	int cap = 0;
	int connector = 0;
	char **args; 
	//char *comm_1 = strtok(inpt, " ");
	char *comm_2 = strtok(inpt, " ");
		
	
//	comm_1 = strtok(inpt," ");
//	char *p = strchr(inpt, '>');
	//printf("found at %d\n", p);
//	if(p != NULL)
//	{
//		std::cout << "hi";
//	}
//	else
//	{
		//std::cout << "bye";
//	}
//	char *comm_2 = strtok(inpt, " ");

	while(comm_2 != NULL)
	{
		findconnectors(comm_2,numarg, args, cap, connector);
		comm_2 = strtok(NULL, " ");
	}
	if(connector == 10)
	{
		//if(connector2 == 10)
		//{
		//	std::cout << "bye";
			tokens2[x] = args;
			x++;
		//}
		//char *a = {"sort", "-r", NULL};
		//const char *b[] = {"sort", "-r", NULL};
		//char *b = new char[3];
		//char **a;
		//strcpy(*a, &b);
		//char **a = &b;
		//char *a = "hi";
		//char *const b[] = {a};
		int pid;
		int pipefd[2];
		if(-1 == pipe(pipefd))
		{
			perror("Error pipe. ");
		}
		pid = fork();
		if(pid == -1)
		{
			perror("Fork error. ");
		}
		else if(pid == 0)
		{
			if(-1 == dup2(pipefd[0], 0))
			{
				perror("Error dup2.");
			}
			if(-1 == close(pipefd[1]))
			{
				perror("Error close. ");
			}
			if(-1 == execvp(tokens2[1][0], tokens2[1]))
			{
				perror("Error execvp. ");
			}
		}
		else if(pid > 0)
		{
			//if(wait(0) == -1)
			//{
			//	perror("Wait error. ");
			//}	
			int pid2;
			pid2 = fork();
			if(pid2 == -1)
			{
				perror("Fork error. ");
			}
			else if(pid2 == 0)
			{
				
				if(-1 == dup2(pipefd[1], 1))
				{
					perror("Error dup2. ");
				}
				if(-1 == close(pipefd[0]))
				{
					perror("Error close. ");
				}
				if(-1 == execvp(tokens2[0][0], tokens2[0]))
				{
					perror("Error execvp. ");
				}
			}
			else if(pid2 > 0)
			{
				if(-1 == close(pipefd[0]))
				{
					perror("Error close. ");
				}
				if(-1 == close(pipefd[1]))
				{
					perror("Error close. ");
				}
				wait(0);
				wait(0);
			}
		}
	}
	if(connector == 2)									//If || dont execute right side
	{
		return;
	}
	if(connector != 6 && connector != 7 && connector != 9 && connector != 10)
	{
		exec(args);
	}	
	if(errorcalled == 1)
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
//	while(usrin != "exit")
//	{
		
//		preparse(cstr);
//	}
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
	//	preparse(cstr);
		parsing(cstr);
	}
	return 0;	
}
