#include "filetypeterm.h"

struct fileattr create_home_dir_node(string path_home){
	struct fileattr home;
	home.f_path = path_home;
	home.f_name = "HOME";
	home.type[0] = 'd';

	return home;
}


bool is_directory(char *path){
	
	bool is_dir=false;
	struct stat pst;

	if(stat(pathname, &st)==0 && S_ISDIR(pst.st_mode)){
		is_dir=true
	}
	return is_dir;
}

bool is_regular_file(char *path){
	
	bool is_file=false;
	struct stat pst;

	if(stat(pathname, &st)==0 && S_ISREG(pst.st_mode)){
		is_file=true
	}
	return is_file;
}

vector<string> parse_file_name(string name){
	vector<string> input = split(name,'|');

	return input;
}
