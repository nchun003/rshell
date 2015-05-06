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

inline bool directory(const char * name) {
    struct stat buffer;
    stat (name, &buffer);
    return S_ISDIR(buffer.st_mode);
}

inline bool exists (const char * name) {
    struct stat buffer;
    return (stat (name, &buffer) == 0);
}

int main(int argc, char ** argv)
{
    if(argc < 3) {
        cout << "ERROR: please enter a destination" << endl;
        return 1;
    }

    if(!exists(argv[1])) {
        cout << "ERROR: input file does exist" << endl;
        return 1;
    }

    string dest = argv[2];

    if(directory(argv[2])) {
        dest.append("/");
        dest.append(argv[1]);
    }

    if(exists(dest.c_str())) {
        cout << "ERROR: destination file already exists" << endl;
        return 1;
    }

    int stat = link(argv[1], dest.c_str());
    if(stat < 0) {
        perror("Failed to link new file");
        return 1;
    }

    int stat2 = unlink(argv[1]);
    if(stat2 < 0) {
        perror("Failed to unlink original file");
        return 1;
    }

    return 0;
}

