/**
 * File: filetype.cpp
 *
 * Receives file name as argument to find_filetype() and determines the type and permissions of the file.
 * Returns file type and permissions as string
 * **/


#include "filetypeperm.h"

using namespace std;

/*int main(int argc, char* argv[]){
	
	string s = find_file_type_permission(argv[1]);
	cout<<s<<"\n";

}*/

/**
 *	@param directory/file 
 *	@return type and permission on the 'dir' passed to the function 
 * **/
string find_file_type_permission(char *dir){

	struct stat pst;

	if(lstat(dir,&pst)<0){
		cerr<<"FATAL:  Could not determine file permissions.";
		exit(1);
	}

	int mode = pst.st_mode;
	
	string type = find_type(mode);

	string permission = find_permission(mode);

	return type+permission;
}


/**
 * @param mode bits of the file 
 * @return type of the file as a single char in string format.
 * **/
string find_type(int mode){
	
	string s="-";	
	
	if ((mode &  0170000) == 0010000)
                //named pipe
                s[0]='p';
        else if ((mode &  0170000) == 0020000)
                // character special file
                s[0]='c';
        else if ((mode &  0170000) == 0040000)
                //directory
                s[0]='d';
        else if ((mode &  0170000) == 0060000)
                // block special file
                s[0]='b';
        else if ((mode &  0170000) == 0100000)
                //regular file
                s[0]='-';
        else if ((mode &  0170000) == 0120000)
                //symbolic link
                s[0]='l';
        else if ((mode &  0170000) == 0140000)
                //socket file
                s[0]='s';
        else
                //unknown file
                s[0]='?';
	return s;
}

/**
 * @param mode bits of the file
 * @return permissions on the file in string format (ugo/rwx)
 * **/
string find_permission(int mode){
	
	string s="---------";

	//owner  permissions
   	if((mode & 0000400) == 0000400) 
		s[0] = 'r';
   	if((mode & 0000200) == 0000200) 
		s[1] = 'w';
   	if((mode & 0000100) == 0000100) 
		s[2] = 'x';
	//group permissions
   	if((mode & 0000040) == 0000040) 
		s[3] = 'r';
   	if((mode & 0000020) == 0000020) 
		s[4] = 'w';
   	if((mode & 0000010) == 0000010) 
		s[5] = 'x';
	//others  permissions
   	if((mode & 0000004) == 0000004) 
		s[6] = 'r';
   	if((mode & 0000002) == 0000002) 
		s[7] = 'w';
   	if((mode & 0000001) == 0000001) 
		s[8] = 'x';
	//special  permissions
   	if((mode & 0004000) == 0004000) 
		s[2] = 's';
   	if((mode & 0002000) == 0002000) 
		s[4] = 's';
   	if((mode & 0001000) == 0001000) 
		s[8] = 't';
	
	return s;
}


