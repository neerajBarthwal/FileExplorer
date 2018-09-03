//Roll Number: 2018201069
//Name       : Neeraj Barthwal

#include "filetypeperm.h"
using namespace std;


void delete_file(string abs_path){
	unlink(abs_path.c_str());
}

void delete_dir(string abs_path){
	cerr<<"\n inside delete: "<<abs_path;
	DIR *dir;
    struct dirent *entry;

    if (!(dir = opendir((char *)abs_path.c_str())))
        return;
    while ((entry = readdir(dir)) != NULL) {
    	
        if (entry->d_type == 4) {
            if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
                continue;
            string file_name=entry->d_name;
            string new_path_fun = abs_path+"/"+file_name;

            delete_dir(new_path_fun);
        } else {
           delete_file(abs_path+"/"+entry->d_name);
        }
    }

    rmdir(abs_path.c_str());

}