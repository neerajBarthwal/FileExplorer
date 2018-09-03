//Roll Number: 2018201069
//Name       : Neeraj Barthwal

#include "filetypeperm.h"
using namespace std;



int create_file(string abs_path){

	int fd = open(abs_path.c_str(), O_RDWR|O_CREAT, 0777);
	if (fd != -1) {
    	close(fd);
	}
	return fd;
}



