#include "filetypeperm.h"
using namespace std;

void rename_file(string old_name, string new_name){

	rename(old_name.c_str(),new_name.c_str());
}