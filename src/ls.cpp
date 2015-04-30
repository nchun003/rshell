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
#include <string.h>
#include <vector>

int flag = 0;

void recursive()
{
}

void all()
{
}

void longlist()
{
}

void get_files(int argc, char** argv, struct dirent *fs, std::vector<std::string> &files)
{
	if(fs->d_name[0] != '.')
	{
		files.push_back(fs->d_name);				//will push back non-hidden files
	}
}

void opendirectory(int argc, char** argv, std::vector<std::string> &files)
{
	DIR *dp;
	if(argv[1] == NULL || flag ==1 )
	{
		dp = opendir(".");
	}
	else{
		dp = opendir(argv[1]);
	}
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
		if(flag == 0)// || flag == 1)
		{
			get_files(argc, argv, filespecs, files);
		}
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

void parsing(int argc, char** argv, std::vector<std::string> files)
{
	std::string a = "-a";
	std::string l = "-l";
	std::string R = "-R";
	std::string av = argv[1];
	if(av == a)
	{
		flag = 1;
		opendirectory(argc, argv, files);
	}
	else if(av == l)
	{
		flag = 2;
		std::cout << "-l called";
	}
	else if(av == R)
	{
		flag = 3;
		std::cout << "-R called";
	}
	else{
	}
	return;
}


	

int main(int argc, char** argv)
{
	std::vector<std::string> params;
	if(argv[1] == NULL)
	{
		opendirectory(argc,argv,params);
		return 0;
	}
	parsing(argc, argv, params);
//	opendirectory(argc, argv);
		
	return 0;
}

