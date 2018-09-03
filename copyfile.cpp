#include "filetypeperm.h"
#define debug(x) cout<<#x<<"="<<x<<endl;
#define correct(x, y, n, m) (0 <= (x) && (x) < (n) && 0 <= (y) && (y) < (m))
#define debug2(x,y) cout<<#x<<"="<<x<<" "<<#y<<"="<<y<<endl;
#define debug3(x,y,z) cout<<#x<<"="<<x<<" "<<#y<<"="<<y<<" "<<#z<<"="<<z<<endl;
#define debug4(x,y,z,w) cout<<#x<<"="<<x<<" "<<#y<<"="<<y<<" "<<#z<<"="<<z<<" "<<#w<<"="<<w<<endl;
#define debug5(x,y,z,w,t) cout<<#x<<"="<<x <<" ";debug4(y,z,w,t);
#define debug6(p,x,y,z,w,t) cout<<#p<<" "<<p<<" "<<#x<<"="<<x <<" ";debug4(y,z,w,t);
#define debug7(o,p,x,y,z,w,t) cout<<#o<<" "<<o<<" ";debug6(p,x,y,z,w,t);


#include <vector>
#include <string>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string>
#include <iostream>
#include <pwd.h>
#include <grp.h>
#include <time.h>
#include <algorithm>
#include <sstream>
#include <sys/stat.h>
#include <dirent.h>
using namespace std;
/**
	param- source 			:absolute path
		   destination 		:absolute path/filename
*/
int copy_files_to_dir(string source, string destination){
	char buffer[1024];
	ssize_t count;
	int destf = open(destination.c_str(), O_WRONLY | O_CREAT | S_IRUSR | S_IWUSR);
    if (destf == -1){
    	cout<<"\n failed in dest";
    	perror("Error: ");
        return -1;
    }

	struct stat pst;
	mode_t org_mode;

	if(stat((char *)(source.c_str()),&pst) != 0){
     	cout<<"stat error!\n"; 
     	return -1;
     }
     org_mode = pst.st_mode;
     	
	int sourcef = open(source.c_str(), O_RDONLY);
    if (sourcef == -1) {
    	cout<<"\n Failed in source: ";
    	return -1;
    }
        	
    while ((count = read(sourcef, buffer, sizeof(buffer))) != 0)
        write(destf, buffer, count);
    fchmod(destf,org_mode);
	
	return 0;

}


void copy_dir_to_dir(string source_name, string source_path, string destination){
    cerr<<"\nIn copy: "<<source_name<<" "<<source_path<<" "<<destination;
    
    DIR *dir;
    struct dirent *entry;
    struct stat fileinfo;
    //debug3(source_name,source_path,destination);
    if (!(dir = opendir((char *)source_path.c_str())))
        return;

    string dest_path_of_source = destination+"/"+source_name;

    if (stat((char *)dest_path_of_source.c_str(), &fileinfo) == -1) {
    	
    	mkdir(dest_path_of_source.c_str(), __mode_t(0777));
    	
	}

    while ((entry = readdir(dir)) != NULL) {
    	
        if (entry->d_type == 4) {
            if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
                continue;
            string source_name=entry->d_name;
            string source_path_fun = source_path+"/"+entry->d_name;

            copy_dir_to_dir(source_name,source_path_fun,dest_path_of_source);
        } else {
           copy_files_to_dir(source_path+"/"+(entry->d_name),dest_path_of_source+"/"+entry->d_name);
        }
    }
    closedir(dir);
}

/*int main(){
    freopen("log2.txt","w",stderr);
    copy_dir_to_dir("a","/home/neeraj/project/OS/fileexplorer/code/a","/home/neeraj/project/OS/fileexplorer/code/b");
    return 0;
}*/