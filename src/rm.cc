#include <iostream>
#include <fstream>
#include <stdio.h>
#include <unistd.h>
#include "errno.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string>
#include <vector>
#include <list>
#include <iterator>
#include <fcntl.h>
#include <dirent.h>
#include <sys/ioctl.h>
#include <stdio.h>
#include <unistd.h>
#include <cmath>
#include <string.h>
#include <sys/stat.h>
#include <grp.h>
#include <pwd.h>
#include <time.h>
#include <locale.h>
#include <langinfo.h>
#include <algorithm>

using namespace std;

void rm(const char * file) {

    struct stat fileStat;
    if(stat(file, &fileStat) < 0) {
        perror("Failed to do filestat");
    }

    bool directory = (S_ISDIR(fileStat.st_mode));

    if(directory) {
        DIR *dirp;
        if(NULL == (dirp = opendir(const_cast<char*>(file)))) {
            perror("Error opening directory.");
        }

        struct dirent *filespecs;
        while(NULL != (filespecs = readdir(dirp))) {
            if(strcmp(filespecs->d_name, ".") == 0 || strcmp(filespecs->d_name, "..") == 0)
                continue;
            string new_file = file;
            new_file.append("/");
            new_file.append(filespecs->d_name);
            rm(new_file.c_str());

        }
        int status;
        status = rmdir(file);
        if(status < 0) {
            cout << file << endl;
            perror("Failed to delete directory");
        }
    }
    else
        unlink(file);
}


int main(int argc, char ** argv)
{
    int start = 1;
    bool recursive = false;

    if(strcmp(argv[start], "-r") == 0) {
        start++;
        recursive = true;
    }


    for(int i = start; i < argc; i++)
    {
        struct stat fileStat;
        if(stat(argv[i], &fileStat) < 0)
            perror("Failed to do filestat");

        bool directory = (S_ISDIR(fileStat.st_mode));

        if(directory && !recursive) {
            cout << "ERROR: Cannot be directory" << endl;
            return 1;
        }
        else if(directory && recursive) {
            string temp = argv[i];
            char back = temp.at(temp.size()-1);
            if(back == '/')
                temp.pop_back();
            rm(temp.c_str());
            /*int status;
            status = rmdir(temp.c_str());
            if(status < 0)
                perror("Failed to delete parent directory");
            */
        }
        else
            rm(argv[i]);
    }
    return 0;
}
