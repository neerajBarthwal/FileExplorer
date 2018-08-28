/**
 * FILE: filesize.cpp
 * This file determines the size of the directory passed to it and returns the size in KB.
 * */


#include "filetypeperm.h"

using namespace std;


/**
 *	@param file name
 *	@return size of the file in KB
 * **/
float find_file_size(char *dir){
	
	 struct stat pst;

        if(lstat(dir,&pst)<0){
                cerr<<"FATAL:  Could not determine file permissions.";
                exit(1);
        }

        float size = pst.st_size/1024;
	return size;
}
