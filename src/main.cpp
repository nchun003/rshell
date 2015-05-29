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
int child = 0;
//int out = 0;
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
//<<<<<<< HEAD
//		if(execvp(argv[0], argv))
//=======
//		std::cout << "Child Process";	
		if(-1 == execvp(argv[0], &argv[0]))
//>>>>>>> redirect
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
	tokens.push_back(token);	
	std::string tokenS(token);
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
	
	if(connector2 == 6)// || connector2 == 8)				//If input
	{
		j[1] = token;
		j[2] = NULL;
		int pid = fork();
		if(pid == -1){
			perror("ERROR!");
			exit(1);
		}
		else if(pid == 0)			//Child process
		{
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
	char col2[] = ";";
	char *coll2 = col2;
	while((result = std::strstr(result, coll2)) != NULL){					//Checks if token contains ';'
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
		if(tokenS.find("<") != 0)
		{
			token[tokenS.find("<")] = '\0';
			j.push_back(token);
		//	std::cout << token[tokenS.find("<")];
		}
		connector2 = 6;
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
	else if(std::string::npos != tokenS.find(">"))/**token == *outt)*/
	{
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
	}
	else if(std::string::npos != tokenS.find("cd"))
	{
		connector2 = 12;
	}
	else if(std::string::npos != tokenS.find("fg"))
	{
		int errorstat = 1;
		if(-1 == kill(child, SIGCONT))
		{
			perror("Kill Error");
		}	
		if(-1 == waitpid(child, &errorstat, WUNTRACED))	
		{
			perror("Error waitpid");
			exit(1);
		}
			
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

	if(connector2 == 1)									//If ; connector was found, everything before is executed
	{
		j.push_back(NULL);
		exec(j);
		connector2 = 0;
		//j = NULL;
		j.clear();
		i = 0;
	}


}
	
void cdfunct(std::vector<char *> c)
{
	if(!c.empty())
	{
		std::string token(c[0]);
		if(std::string::npos != token.find("-"))
		{
			if(-1 == chdir(getenv("OLDPWD")))
			{
				perror("Error getnv/ chdir");
			}
			std::cout << get_current_dir_name() << std::endl;
			return;
		}
		const char *b = c[0];
		if(-1 == setenv("OLDPWD", getenv("PWD"), 1))
		{
			perror("Error getnv/chdir");
		}
		if(-1 == chdir(b))
		{
			perror("Error chdir. ");
		}

	}	
	else if(c.empty())
	{
		if(-1 == setenv("OLDPWD", getenv("PWD"), 1))
		{
			perror("Error getnv/chdir");
		}

		if(-1 == chdir(getenv("HOME")))
		{
			perror("Error getenv/chdir");
		}	
	}
}


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
		
	while(comm_2 != NULL)
	{
		findconnectors(comm_2,numarg, args, cap, connector);
		comm_2 = strtok(NULL, " ");
	}
	if(connector == 10 || connector == 8)
	{
		args.push_back(NULL);
		tokens2.push_back(args);
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
	if(connector == 12)
	{
		cdfunct(args);	
	}
	if(connector != 6 && connector != 7 && connector != 9 && connector != 10 && connector != 8 && connector != 12)
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

static void handler(int signum)
{
	if(signum == SIGINT){
		return;
	}
	else if(signum == SIGTSTP)
	{
		int pid = fork();
		if(pid == -1){
			perror("ERROR!");
			exit(1);
		}
		else if(pid == 0)			//Child process
		{
			raise(SIGSTOP);
			exit(1);			//Child killed when done with task
		}
		else if(pid > 0)
		{
			/*if(wait(0) == -1)		//Waits for child process to finish
			{	
				perror("Wait error!");
			}*/
		}

	//	raise(SIGSTOP);			
		return;
	}
		
}
	
int main(int argc, char **argv)
{
	struct sigaction sa;
	sa.sa_handler = handler;
	sa.sa_flags = SA_RESTART;
	
	if(-1 == sigaction(SIGINT, &sa, NULL))
	{
		perror("Error sigaction");	
	}
	if(-1 == sigaction(SIGTSTP, &sa, NULL))
	{
		perror("Error sigaction. ");
	}
//	pid_t pid = fork();
/*	if(-1 == pid)
	{
		perror("fork error");
	}
	else if(0 == pid)
	{
*/
	std::string usrin;
	while(usrin != "exit")
	{
		userlogin();
		char *buffer = get_current_dir_name();
		std::string dirname(buffer);
		if(std::string::npos != dirname.find("/home/csmajs/nchun003"))
		{
			dirname.replace(0, 21, "~");	
		}
		free(buffer);
		std::cout << ":" << dirname << " ";
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
