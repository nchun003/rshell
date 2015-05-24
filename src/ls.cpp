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

bool flag = true;
bool flaga = false;
bool flagl = false;
bool flagr = false;
int direcsize = 0;

void longlist(const char* path, unsigned fs, unsigned bt)
{
	std::cout << std::endl;	
	struct stat buf;
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

void order(std::vector<std::string> &f3, std::vector<std::string> d5)
{
	const char* temp;
	unsigned blktotal = 0;
	unsigned filesize = 0;
	std::sort(f3.begin(), f3.end(), compare);
	if((flag && !flagl && !flagr) || (flaga && !flagl && !flagr) || (flagr&&!flagl&&!flaga))
	{	
		for(unsigned i=0; i<f3.size(); i++)
		{
			std::cout << f3[i] << "  ";
		}
		if(flagr)
		{
			std::cout << std::endl;
		}
	}
	

	if(flagl)// && !flagr)
	{
		for(unsigned j=0; j<f3.size(); j++)
		{
			struct stat buf;
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
			temp = f3[i].c_str();
			longlist(temp,filesize,blktotal);
		}
		
	}
	return;			
}

void get_files(struct dirent *fs, std::vector<std::string> &f2)
{
	if(flaga)// || flag == 4)
	{
		f2.push_back(fs->d_name);
	}
	else if(fs->d_name[0] != '.')
	{
		f2.push_back(fs->d_name);				//will push back non-hidden files
	}
	return;
}

void opendirectory(int argc, char** argv, std::vector<std::string> &f1, std::vector<std::string> &d2)
{
	DIR *dp;
	if(argv[1] == NULL || flaga || flagl || flagr)// || flag ==4)
	{
		d2.push_back(".");
		direcsize++;
		dp = opendir(".");
		if(NULL == dp)
		{
			perror("Opendir Error");
		}
	}
	else{
		d2.push_back(argv[1]);
		direcsize++;
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
		if(flag || flaga || flagl || flagr)// || flag == 1)
		{
			get_files(filespecs, f1);
		}
//		std::cout << filespecs->d_name << " ";
	}
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
//	if(!flagr && !flagl)
//	{
		order(f1, d2);
//	}
	if(!flagr)
	{
		std::cout << std::endl;
	}
	return;
}


void opendirectoryR(std::string ss, std::vector<std::string> &d4)
{
	d4.push_back(ss);
	direcsize++;
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

	unsigned blktotal2 = 0;
	unsigned filesize2 = 0;

	if(flagl && flagr)
	{	
		std::sort(f1.begin(), f1.end(), compare);
				for(unsigned j=0; j<f1.size(); j++)
		{
			struct stat buf;
	//		stat ((d4[direcsize-1]+"/"+f1[j]).c_str(), &buf);
			if(-1 == stat((d4[direcsize-1]+"/"+f1[j]).c_str(), &buf))
			{
				perror("Stat Error");
				exit(0);
			}
			std::ostringstream ss;
			ss << buf.st_size;
			std::string s = ss.str();
			//std::string s = buf.st_size;
			if(s.size() > filesize2)
			{
				filesize2 = s.size()+2;
			}
			blktotal2 += buf.st_blocks;
		}

		std::cout << "total: " << blktotal2/2;
		for(unsigned i=0; i<f1.size(); i++)
		{
			longlist((d4[direcsize-1]+"/" + f1[i]).c_str(), filesize2, blktotal2);
		}
		std::cout << std::endl;
		return;
	}

	
		
	order(f1, d4);

	for(unsigned j=0; j<f1.size(); j++)
	{
		std::string path  = d4[direcsize-1] + "/" + f1[j];
		struct stat buf;
	//	stat (path.c_str(), &buf);
		if(-1 == stat(path.c_str(), &buf))
		{
			perror("Stat Error");
			exit(0);
		}
		if(buf.st_mode & S_IFDIR) 
		{
			std::cout << std::endl;
			std::cout << d4[direcsize-1] << "/" << f1[j] << ": " << std::endl;
			opendirectoryR(path, d4);
		//	opendirectory(files[j].size, files[j], files);	
		}
		
	}
//	}

}
	

void parsing(int argc, char** argv, std::vector<std::string> &files, std::vector<std::string> &d)
{
	std::string a = "-a";
	std::string a2 = "a";
	char *ay = new char [a2.length() +1];
	strcpy(ay, a2.c_str());
	std::string l = "-l";
	std::string l2 = "l";
	char *la = new char [l2.length() +1];
	strcpy(la, l2.c_str());
	std::string R = "-R";
	std::string R2 = "R";
	char *Ra = new char [R2.length() +1];
	strcpy(Ra, R2.c_str());
	for(int i=1; i<argc; i++)
	{
		char *r = argv[i];
		if((r=std::strstr(r, ay)) != NULL)
		{
			flaga = true;
		}
		r = argv[i];
		if((r=std::strstr(r, la)) != NULL)
		{
			flagl = true;
		}
		r = argv[i];
		if((r=std::strstr(r, Ra)) != NULL)
		{
			flagr = true;
		}


		std::string av = argv[i];
		if(av == a)
		{
			flaga = true;
		}
		if(av == l)
		{
			flagl = true;
		}
		if(av == R)
		{
			flagr = true;
		}
	}
	if(flaga && !flagl && !flagr)// && av2 != l)
	{
//		flaga = true;
		opendirectory(argc, argv, files, d);
		return;
	}
	if(flagl && !flagr)//av == l || av2 == l)
	{
//		flagl = true;
		opendirectory(argc, argv, files, d);
		return;
	//	longlist(argv[1]);
	}
	if(flagr)//av == R || av2 == R)
	{
//		flagr = true;
		std::cout << ".:"<< std::endl;
		opendirectory(argc, argv, files, d);
		for(unsigned j=0; j<files.size(); j++)
		{
			std::string path = d[0] + "/" + files[j];
			struct stat buf;
	//		stat (path.c_str(), &buf);
			if(-1 == stat(path.c_str(), &buf))
			{
				perror("Stat Error");
				exit(0);
			}
			if(buf.st_mode & S_IFDIR) 
			{
				std::cout << std::endl;
				if(flagl)
				{
					std::cout << std::endl;
				}
				std::cout << d[0] << "/" << files[j] << ": " << std::endl;
//				std::cout << "path:" << path;
				opendirectoryR(path, d);
			//	opendirectory(files[j].size, files[j], files);	
			}

			
		}
		//checkrec(files);
	}
	else{
		opendirectory(argc, argv, files, d);
	}
	return;
}


	

int main(int argc, char** argv)
{
	std::vector<std::string> params;
	std::vector<std::string> directory;
	if(argv[1] == NULL)
	{
		opendirectory(argc,argv, params, directory);
		return 0;
	}
	parsing(argc, argv, params, directory);
//	opendirectory(argc, argv);
		
	return 0;
}

