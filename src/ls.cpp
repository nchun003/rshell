#include <stdio.h>
#include <errno.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <iostream>
#include <stdlib.h>
#include <fcntl.h>
#include <cstring>
#include <string>

void parsing(int argc, char** argv, int &f)
{
	std::string a = "-a";
	char *cstra = new char [a.length()+1];
	strcpy(cstra, a.c_str());
	std::string l = "-l";
	char *cstrl = new char [l.length()+1];
	strcpy(cstrl, l.c_str());
	std::string R = "-R";
	char *cstrR = new char [R.length()+1];
	strcpy(cstrR, R.c_str());
	if(*argv[1].at(1) == *cstra)
	{
		f = 1;
		std::cout << "-a called";
	}
	else if(*argv[1] == *cstrl)
	{
		f = 2;
		std::cout << "-l called";
	}
	else if(*argv[1] == *cstrR)
	{
		f = 3;
		std::cout << "-R called";
	}
	return;
}

void opendirectory(int argc, char** argv)
{
	DIR *dp = opendir(argv[1]);
	if(NULL == dp)
	{
		perror("There was an error with opendir(). ");
	//	std::cout <<argv[1];
		exit(1);
	}
	struct dirent *filespecs;
	errno = 0;
	while(NULL != (filespecs = readdir(dp)))
	{
		std::cout << filespecs->d_name << " ";
	}
	if(errno != 0)
	{
		perror("THere was an error with readdir(). ");
		exit(1);
	}
	std::cout << std::endl;
	if(-1 == closedir(dp))
	{
		perror("There was an error with closedir(). ");
		exit(1);
	}
	return;
}
	

int main(int argc, char** argv)
{
	int flag = 0;			//1 = -a, 2 = -l, 3 = -R
	parsing(argc, argv, flag);
	opendirectory(argc, argv);
		
	return 0;
}

