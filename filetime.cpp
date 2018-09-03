//Roll Number: 2018201069
//Name       : Neeraj Barthwal
#include "filetypeperm.h"

using namespace std;

string find_file_mod_time(char *dir){
	struct stat pst;
	
        if(stat(dir,&pst)<0){
                cerr<<"FATAL:  Could not determine file time.";
                exit(1);
        }

	long seconds = pst.st_mtime;

	string stime = ctime(&seconds);
	
	if (!stime.empty() && stime[stime.length()-1] == '\n') {
    		stime.erase(stime.length()-1);
	}	
	return stime;

}
