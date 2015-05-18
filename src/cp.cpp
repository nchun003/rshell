#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <iostream>
#include <fstream>
#include <vector>

#include "Timer.h"

using namespace std;

// Copies a file by streaming each byte from the source to the destination
int copyStream(char* sourceName, char* destName)
{
	ifstream ifs(sourceName);
	ofstream ofs(destName);
	char c;
	while (ifs.get(c) )
	{
		ofs << c;
	}
	return 0;
}

// Copies a file using syscalls, one byte at a time
int copyChar(int source, int dest)
{
	char buf;
	int copyState = 1;
	while (copyState)
	{
		copyState = read(source, &buf, 1);
		if (copyState < 0)
		{
			perror("read");
			return 1;
		}
		else if (!copyState) break;
		copyState = write(dest, &buf, 1);
		if (copyState <= 0)
		{
			perror("write");
			return 1;
		}
	}
	return 0;
}

// Copies a file using syscalls, with buffering
int copyBuffer(int source, int dest)
{
	char buf[BUFSIZ];
	int copyState = 1;
	while (copyState)
	{
		copyState = read(source, &buf, BUFSIZ);
		if (copyState < 0)
		{
			perror("read");
			return 1;
		}
		else if (!copyState) break;
		copyState = write(dest, &buf, BUFSIZ);
		if (copyState <= 0)
		{
			perror("write");
			return 1;
		}
	}
	return 0;
}

int main(int argc, char** argv)
{
	Timer t;
	double timeWall;
	double timeUser;
	double timeSystem;

	int ret = 0;
	if (argc < 3)
	{
		cerr << "Usage: cp <source> <destination> [<benchmark>]" << endl;
		return 1;
	}

	int source = open(argv[1], O_RDONLY);
	if (source < 0)
	{
		perror("open");
		return 1;
	}

	if (argc > 3)
	{
		argv[2][0] = '1';
		cout << "Timing copyStream()... " << endl;
		t.start();
		ret = copyStream(argv[1], argv[2]);
		t.elapsedTime(timeWall, timeUser, timeSystem);
		cout << "Wallclock time: " << timeWall << endl;
		cout << "User time: " << timeUser << endl;
		cout << "System time: " << timeSystem << endl;

		argv[2][0] = '2';
		int dest2 = open(argv[2], O_CREAT|O_EXCL|O_WRONLY, S_IRWXU|S_IRGRP|S_IROTH);
		if (dest2 < 0)
		{
			perror("open");
			if(-1 == close(source))
			{
				perror("Close Error");
			}
			return 1;
		}

		cout << "Timing copyChar()... " << endl;
		t.start();
		ret = copyChar(source, dest2);
		t.elapsedTime(timeWall, timeUser, timeSystem);
		cout << "Wallclock time: " << timeWall << endl;
		cout << "User time: " << timeUser << endl;
		cout << "System time: " << timeSystem << endl;
		if(-1 == close(dest2))
		{
			perror("Close Error");
		}

		argv[2][0] = '3';
		int dest3 = open(argv[2], O_CREAT|O_EXCL|O_WRONLY, S_IRWXU|S_IRGRP|S_IROTH);
		if (dest3 < 0)
		{
			perror("open");
			if(-1 == close(source))
			{
				perror("Error Close");
			}
			return 1;
		}

		cout << "Timing copyBuffer()... " << endl;
		t.start();
		ret = copyBuffer(source, dest3);
		t.elapsedTime(timeWall, timeUser, timeSystem);
		cout << "Wallclock time: " << timeWall << endl;
		cout << "User time: " << timeUser << endl;
		cout << "System time: " << timeSystem << endl;
		if(-1 == close(dest3))
		{
			perror("Close Error");
		}
	}
	else
	{
		int dest = open(argv[2], O_CREAT|O_EXCL|O_WRONLY, S_IRWXU|S_IRGRP|S_IROTH);
		if (dest < 0)
		{
			perror("open");
			if(-1 == close(source))
			{
				perror("Close Error");
			}
			return 1;
		}

		ret = copyBuffer(source, dest);
		if(-1 == close(dest))
		{
			perror("Close Error");
		}
	}

	if(-1 == close(source))
	{
		perror("Close Error");
	}
	ret = 0;
	return ret;
}
