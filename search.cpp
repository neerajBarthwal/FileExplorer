//Roll Number: 2018201069
//Name       : Neeraj Barthwal
#include "filetypeperm.h"

using namespace std;
vector<struct fileattr> fs_search;
void search(string filename,string absolute_path){
	cerr<<"\n in search searhin for "<<filename;
    DIR *dir;
    struct dirent *entry;

    if (!(dir = opendir(absolute_path.c_str())))
        return;

    while ((entry = readdir(dir)) != NULL) {
        if (entry->d_type == 4) {
            if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
                continue;
            if(entry->d_name==filename){
            	cerr<<"\n one match";
            	struct fileattr node;
            	node.f_name = filename;
            	node.f_path = absolute_path+"/"+filename;
            	fs_search.push_back(node);
            }

            string absolute_path_new = absolute_path+"/"+entry->d_name;
            search(filename,absolute_path_new);
        } else {
            if(entry->d_name==filename){
            	struct fileattr node;
            	node.f_name = filename;
            	node.f_path = absolute_path+"/"+filename;
            	fs_search.push_back(node);
            }
        }
    }
    closedir(dir);
    cerr<<"size of search: "<<fs_search.size();
    display_search_result();
}

