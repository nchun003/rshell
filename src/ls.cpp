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
#include <pwd.h>
#include <grp.h>
#include <iomanip>
#include <sstream>

int flag = 0;

void recursive()
{
}

void all()
{
}

void longlist(const char* path, unsigned &fs, unsigned bt)
{
	std::cout << std::endl;	
	struct stat buf;
	stat (path, &buf);
	if(-1 == stat(path, &buf))
	{
		perror("Stat Error");
		exit(0);
	}


	buf.st_mode & S_IFDIR? std::cout << "d":std::cout << "-";
	buf.st_mode & S_IRUSR? std::cout << "r":std::cout << "-";
	buf.st_mode & S_IWUSR? std::cout << "w":std::cout << "-";
	buf.st_mode & S_IXUSR? std::cout << "x":std::cout << "-";
	buf.st_mode & S_IRGRP? std::cout << "r":std::cout << "-";
	buf.st_mode & S_IWGRP? std::cout << "w":std::cout << "-";
	buf.st_mode & S_IXGRP? std::cout << "x":std::cout << "-";
	buf.st_mode & S_IROTH? std::cout << "r":std::cout << "-";
	buf.st_mode & S_IWOTH? std::cout << "w":std::cout << "-";
	buf.st_mode & S_IXOTH? std::cout << "x":std::cout << "-";

	std::cout << " " << buf.st_nlink;
	
	struct passwd *pw = getpwuid(buf.st_uid);
	if(pw == NULL)
	{
		perror("Getpwuid Error");
	}
	else{
		std::cout << " " << pw->pw_name;
	}

	struct group *gr = getgrgid(buf.st_gid);
	if(gr == NULL)
	{
		perror("Getgrgid Error");
	}
	else{
		std::cout << " " << gr->gr_name;
	}
	std::cout.width(fs); std::cout << std::right << buf.st_size;

	char timebuff[13];
	char* dattime = timebuff;
	struct tm *mytm = localtime(&buf.st_mtime);
	strftime(dattime, 13, "%h %e %H:%M", mytm);
	std::cout.width(13); std::cout << std::right  <<  dattime << " ";

	std::cout << path;
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
	const char* temp;
	unsigned blktotal = 0;
	unsigned filesize = 0;
//	std::string temps; 
	std::sort(f3.begin(), f3.end(), compare);
	if(flag == 0 || flag == 1 || flag == 3)
	{	
		for(unsigned i=0; i<f3.size(); i++)
		{
			std::cout << f3[i] << "  ";
		}
		if(flag == 3)
		{
			std::cout << std::endl;
		}
	}
	else if(flag == 2)// || flag == 4)
	{
		for(unsigned j=0; j<f3.size(); j++)
		{
			struct stat buf;
			stat (f3[j].c_str(), &buf);
			if(-1 == stat(f3[j].c_str(), &buf))
			{
				perror("Stat Error");
				exit(0);
			}
			std::ostringstream ss;
			ss << buf.st_size;
			std::string s = ss.str();
			//std::string s = buf.st_size;
			if(s.size() > filesize)
			{
				filesize = s.size()+2;
			}
			blktotal += buf.st_blocks;
		}
		std::cout << "total " << blktotal/2;
		for(unsigned i=0; i<f3.size(); i++)
		{
//			temps = "./" +  f3[i];
//			temp = temps.c_str(); 
			temp = f3[i].c_str();
//		//	temp = temps;
//			temp = temps;
//			char* ptr = temp;
		//	std::cout << temp << std::endl;
			longlist(temp,filesize,blktotal);
//			struct stat buf;
//			stat (temp, &buf);
		//	mode_t t;
			//	int result = fstat(path, &buf);
			//	if(!result)
			//	{
			//		exit(-1);
			//	}
//			if(-1 == stat(temp, &buf))
//			{
//				perror("Stat Error");
//				exit(0);
//			}
		//	mode_t p = buf.st_mode;
//			if(buf.st_mode & S_IFDIR)
//			{
//				std::cout << "d" << std::flush;
//			}
//			else{
//				std::cout << "-" << std::flush;
//			}

		}
		
//		longlist(temp);
	}
	return;			
}

void get_files(struct dirent *fs, std::vector<std::string> &f2)
{
	if(flag == 1)// || flag == 4)
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
	if(argv[1] == NULL || flag ==1 || flag ==2 || flag ==3)// || flag ==4)
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
		if(flag == 0 || flag == 1 || flag ==2 || flag == 3)// || flag == 1)
		{
			get_files(filespecs, f1);
		}
//		std::cout << filespecs->d_name << " ";
	}
//	order(f1);
	if(errno != 0)
	{
		perror("THere was an error with readdir(). ");
		exit(1);
	}
//	std::cout << std::endl;
	if(-1 == closedir(dp))
	{
		perror("There was an error with closedir(). ");
		exit(1);
	}
	order(f1);
	std::cout << std::endl;
	return;
}


void opendirectoryR(std::string ss)
{
//	for(unsigned j=0; j<v.size(); j++)
//	{
//		struct stat buf;
//		stat (v[j].c_str(), &buf);
//		if(-1 == stat(v[j].c_str(), &buf))
//		{
//			perror("Stat Error");
//			exit(0);
//		}
//		if(buf.st_mode & S_IFDIR) 
//		{
//			std::cout << "./" << v[j] << ": " << std::endl;
//			opendirectoryR(v[j]);
//		//	opendirectory(files[j].size, files[j], files);	
//		}		
//	}
	std::vector<std::string> f1;
	DIR *dp;
	const char* s = ss.c_str();
	dp = opendir(s);
	if(NULL == dp)
	{
		perror("There was an error with opendir(). ");
		exit(1);
	}
	struct dirent *filespecs;
	errno = 0;
	while(NULL != (filespecs = readdir(dp)))
	{
			get_files(filespecs, f1);
	}
	if(errno != 0)
	{
		perror("THere was an error with readdir(). ");
		exit(1);
	}
	if(-1 == closedir(dp))
	{
		perror("There was an error with closedir(). ");
		exit(1);
	}
	order(f1);
}
	

void parsing(int argc, char** argv, std::vector<std::string> &files)
{
	std::string a = "-a";
	std::string l = "-l";
	std::string R = "-R";
	std::string av = argv[1];
//	std::string av2 = argv[2];
	if(av == a)// && av2 != l)
	{
		flag = 1;
		opendirectory(argc, argv, files);
	}
	else if(av == l)
	{
		flag = 2;
		opendirectory(argc, argv, files);
	//	longlist(argv[1]);
	}
	else if(av == R)
	{
		flag = 3;
		std::cout << ".:"<< std::endl;
		opendirectory(argc, argv, files);
		for(unsigned j=0; j<files.size(); j++)
		{
			struct stat buf;
			stat (files[j].c_str(), &buf);
			if(-1 == stat(files[j].c_str(), &buf))
			{
				perror("Stat Error");
				exit(0);
			}
			if(buf.st_mode & S_IFDIR) 
			{
				std::cout << std::endl;
				std::cout << "./" << files[j] << ": " << std::endl;
				opendirectoryR(files[j]);
			//	opendirectory(files[j].size, files[j], files);	
			}

			
		}
		//checkrec(files);
	}
//	else if(av == a && av2 == l)
//	{
//		std::cout << "hi";
//		flag = 4;
//		opendirectory(argc, argv, files);
//	}
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

