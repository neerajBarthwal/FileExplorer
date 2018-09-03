#include "filetypeperm.h"

using namespace std;
void create_dir(string abs_path){

	struct stat st;

	if (stat(abs_path.c_str(), &st) == -1) {
	    mkdir(abs_path.c_str(), __mode_t(0700));
	}
}