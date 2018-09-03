//Roll Number: 2018201069
//Name       : Neeraj Barthwal
#include "filetypeperm.h"
#include <fstream>
using namespace std;
ofstream snapfile;

void do_snap(string source){
	DIR *dir;
    struct dirent *entry;

    if (!(dir = opendir(source.c_str())))
        return;

    while ((entry = readdir(dir)) != NULL) {
        if (entry->d_type == 4) {
            if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
                continue;
            string absolute_path = source+"/"+entry->d_name;
            snapfile<<absolute_path<<"\n";
            do_snap(absolute_path);
        } else {
        	string absolute_path = source+"/"+entry->d_name;
            snapfile<<absolute_path<<"\n";
        }
    }
    closedir(dir);
}

void snapshot(string source, string destination){
	cerr<<"in snapshot";
	snapfile.open (destination);
  	do_snap(source);
}

