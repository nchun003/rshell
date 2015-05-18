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

void exec(std::vector<char *> &argv)//char **&argv)
{
	errorcalled = 0;
	int pid = fork();
	if(pid == -1){
		perror("ERROR!");
		exit(1);
	}
	else if(pid == 0)			//Child process
	{
<<<<<<< HEAD
		if(execvp(argv[0], argv))
=======
//		std::cout << "Child Process";	
		if(-1 == execvp(argv[0], &argv[0]))
>>>>>>> redirect
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







int o = 0;
std::vector<char *> tokens;
std::vector<std::vector<char *>> tokens2;
int x = 0;
void  findconnectors(char *token,int &i, std::vector<char *> &j, int &capacity, int &connector2)		//Checks if a token is a connector
{
	//std::vector<char *> tokens;
	tokens.push_back(token);	
	std::string tokenS(token);


//	std::string out1 = ">";
//	char *outt = new char [out1.length()+1];
//	strcpy(outt, out1.c_str());
	
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
//			j.push_back(NULL);
			if(-1 == execvp(j[0], &j[0]))//tokens[0], b))//tokens[0], b))
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
			j.push_back(NULL);
			if(-1 == execvp(j[0], &j[0]))
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

	if(connector2 == 7 || connector2 == 8)				//If output
	{
		int saveout;
		if(-1 == (saveout = dup(1)))
		{
			perror("Error with dup. ");
		}
		const char *b = token;
		o = open(b, O_WRONLY |O_TRUNC | O_CREAT, S_IRUSR | S_IRGRP | S_IWGRP | S_IWUSR);
		if(connector2 == 7){
		if(o == -1)		{
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
			j.push_back(NULL);
			if(-1 == execvp(j[0], &j[0]))
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
	if(std::string::npos != tokenS.find("#"))//*/*token == *comn)
	{
		j.push_back(NULL);
		exec(j);
		//j = NULL;
		j.clear();
		i = 0;
		connector2 = 5;
	//	free(comn);
		return;
	}
	if(connector2 == 4)									//&& failed
	{
		return;
	}
	
	if(std::string::npos != tokenS.find(";"))//*/*token == *coll)									//If token is ; everything before it will get executed
	{
		connector2 = 1;
		j.push_back(NULL);
		exec(j);
		//j = NULL;
		j.clear();
		i = 0;
		//delete []coll;
		return;
	}
	char *result = token;
<<<<<<< HEAD
	while((result = std::strstr(result, coll)) != NULL){					//Checks if token contains ';'
=======
	char col2[] = ";";
	char *coll2 = col2;
	while((result = std::strstr(result, coll2)) != NULL){					//Checks if token contains ';'
//		std::cout << "Found " << coll << "starting at " << result << std::endl;
>>>>>>> redirect
		strncpy(result, "\0", 2);
		if(connector2 == 2)
		{
			//j = NULL;
			j.clear();
			i = 0;
			connector2 = 0;
			return;
		}
		connector2 = 1;
		++result;
	//	free(coll);
	}
	if(std::string::npos != tokenS.find("||"))//*/*token == *orr)									//Everything before || will get executed
	{
		if(connector2 == 2)								//If or command already succeeded, leave
		{
			//j = NULL;
			j.clear();
			i = 0;
			return;
		}
		connector2 = 2;
		j.push_back(NULL);
		exec(j);
		if(errorcalled == 1)								//If or failed try next command
		{
			connector2 = 0;
			
		}
		//j = NULL;
		j.clear();
		i = 0;
		return;		
	} 
	if(std::string::npos != tokenS.find("|"))//*/*token == *p2)
	{
		if(tokenS.find("|") != 0)
		{
			token[tokenS.find("|")] = '\0';
			j.push_back(token);
		}
		connector2 = 10;
		//tokens2[x] = j;
	//	tokens2[x] = &j[0];
		j.push_back(NULL);
		tokens2.push_back(j);
		//std::vector<char *>v = tokens2[0];
		//std::cout << v[0];
		x++;
		//j = NULL;
		j.clear();
		i = 0;
		//int z = i-1;
		//j[z] = NULL;
	//	free(p2);
		return;
	}

	//std::string sand = "&&";
	//char *andd = new char [sand.length()+1];
	//strcpy(andd, sand.c_str());

	else if(std::string::npos != tokenS.find("&&"))//*/*token == *andd)
	{
		connector2 = 3;
		j.push_back(NULL);
		exec(j); 
		if(errorcalled == 1)
		{
			connector2 = 4;
		}
	//	j = NULL;
		i = 0;
		//free(andd);
		return;
	}
	else if(std::string::npos != tokenS.find("<"))//*/*token == *inn)
	{
	//	int fd[2];
	//	pipe(fd);
	//	dup(fd[0]);
		/*if(connector2 == 8)
		{}
		else{*/
		if(tokenS.find("<") != 0)
		{
			token[tokenS.find("<")] = '\0';
			j.push_back(token);
		//	std::cout << token[tokenS.find("<")];
		}
		connector2 = 6;
	//	}	
//		j = NULL;
//		i = 0; 
		//redirection(j);
	//	exec(j);
	//	return;
	//	delete []inn;
	}
	else if(std::string::npos != tokenS.find(">>"))
	{
		if(tokenS.find(">>") != 0)
		{
			token[tokenS.find(">>")] = '\0';
			j.push_back(token);
		}
		connector2 = 9;
	}
//	else if(*token == *outt2)
//	{
//		std::cout << "double out";
//	}
	else if(std::string::npos != tokenS.find(">"))/**token == *outt)*/
	{
	//	if(connector2 == 8)
	//	{
	//		return;
	//	}
	//	else{
		if(tokenS.find(">") != 0)
		{
			token[tokenS.find(">")] = '\0';
			j.push_back(token);
		}
		if(connector2 == 10)
		{
			connector2 = 8;
		}
		else{
			connector2 = 7;
		}
	//	}
//		j = NULL;
//		i = 0;
	//	delete []outt;
	}
	else{											//If token is not connector it will get put in j(argv)
		if(connector2 == 2)
		{
			return;
		}			
		++i;
		j.push_back(token);
				return;
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
		j.push_back(NULL);
		exec(j);
		connector2 = 0;
		//j = NULL;
		j.clear();
		i = 0;
	}


}
	

/*void piping()
{
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
			//for(int i = 0; i <= 1 ; ++i)
			//{
			close(pipefd[1]);
			close(pipefd[0]);
			piping;
		}
}
*/	
void parsing(char *inpt)									//parses by using spaces
{
//	std::cout << "parsing called";
//	int out = 0;
	int numarg = 0;
	int cap = 0;
	int connector = 0;
	//char **args; 
	std::vector<char *> args;
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
	if(connector == 10 || connector == 8)
	{
		args.push_back(NULL);
		tokens2.push_back(args);
		//args.push_back(NULL);
		//tokens2.push_back(args);
		//if(connector2 == 10)
		//{
		//	std::cout << "bye";
			//tokens2[x] = args;
			//tokens2[x] = &args[0];
	//		tokens2.push_back(args);
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
		if(connector == 8)
		{
			int saveout;
			if(-1 == (saveout = (dup(1))))
			{
				perror("Dup error");
			}
			if(o == -1)		{
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
				int pid3;
				int pipefd[2];
				if(-1 == pipe(pipefd))
				{
					perror("Error pipe. ");
				}
				pid3 = fork();
				if(pid3 == -1)
				{
					perror("Fork error. ");
				}
				else if(pid3 == 0)
				{
					if(-1 == dup2(pipefd[0], 0))
					{
						perror("Error dup2.");
					}
					if(-1 == close(pipefd[1]))
					{
						perror("Error close. ");
					}
					tokens2[0].push_back(NULL);
					if(-1 == execvp(tokens2[1][0], &tokens2[1][0]))
					{
						perror("Error execvp. ");
					}
				}
				else if(pid3 > 0)
				{
					//if(wait(0) == -1)
					//{
					//	perror("Wait error. ");
					//}	
					//for(int i = 0; i <= 1 ; ++i)
					//{
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
						tokens2[1].push_back(NULL);
						if(-1 == execvp(tokens2[0][0], &tokens2[0][0]))
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
						if(-1 == wait(0))
						{
							perror("Error wait. ");
						}
						if(-1 == wait(0))
						{
							perror("Error wait. ");
						}
					}//}
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
		}
		else{
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
				tokens2[0].push_back(NULL);
				if(-1 == execvp(tokens2[1][0], &tokens2[1][0]))
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
				//for(int i = 0; i <= 1 ; ++i)
				//{
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
					tokens2[1].push_back(NULL);
					if(-1 == execvp(tokens2[0][0], &tokens2[0][0]))
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
					if(-1 == wait(0))
					{
						perror("Error wait. ");
					}
					if(-1 == wait(0))
					{
						perror("Error wait. ");
					}
				}//}
			}
		}

		tokens2.clear();
	}
	if(connector == 2)									//If || dont execute right side
	{
		return;
	}
	if(connector != 6 && connector != 7 && connector != 9 && connector != 10 && connector != 8)
	{
		args.push_back(NULL);
		exec(args);
	}	
	if(errorcalled == 1)
	{
		exit(0);
	}
//	delete [] args;
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
		delete []cstr;
	}
	return 0;	
}
