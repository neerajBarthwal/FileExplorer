#include "filetypeperm.h"

using namespace std;
void move_dir_to_dir(string source, string source_path, string destination){
	copy_dir_to_dir(source, source_path, destination);
	delete_dir(source_path);

}

void move_files_to_dir(string source, string destination){
	copy_files_to_dir(source,destination);
	delete_file(source);
}