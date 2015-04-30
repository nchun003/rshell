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
#include <algorithm>
#include <ctype.h>

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

bool compare(std::string i, std::string j)
{
	std::string temp;
	std::string temp2;
	unsigned n = 0;
	if(i[0] == '.')
	{
		n = 1;
	}
	for(unsigned x = n; x<i.size(); x++)
	{		
		char s =  tolower(i[x]);
		std::string s2;
		temp += s;
	}
	if(j[0] == '.')
	{
		n = 1;
	}
	else{
		n = 0;
	}
	for(unsigned y=n; y<j.size(); y++)
	{
		char s = tolower(j[y]);
		std::string s2;
		temp2 += s;
	}
	return	(temp < temp2);
}

void order(std::vector<std::string> &f3)
{
	std::sort(f3.begin(), f3.end(), compare);
	for(unsigned i=0; i<f3.size(); i++)
	{
		std::cout << f3[i] << "  ";
	}	
}

void get_files(struct dirent *fs, std::vector<std::string> &f2)
{
	if(flag == 1)
	{
		f2.push_back(fs->d_name);
	}
	else if(fs->d_name[0] != '.')
	{
		f2.push_back(fs->d_name);				//will push back non-hidden files
	}
	return;
}

void opendirectory(int argc, char** argv, std::vector<std::string> &f1)
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
		if(flag == 0 || flag == 1)// || flag == 1)
		{
			get_files(filespecs, f1);
		}
//		std::cout << filespecs->d_name << " ";
	}
	order(f1);
//	std::cout << f1[0];
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

void parsing(int argc, char** argv, std::vector<std::string> &files)
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
		opendirectory(argc, argv, files);
	}
	return;
}


	

int main(int argc, char** argv)
{
	std::vector<std::string> params;
	if(argv[1] == NULL)
	{
		opendirectory(argc,argv, params);
		return 0;
	}
	parsing(argc, argv, params);
//	opendirectory(argc, argv);
		
	return 0;
}

