//Roll Number: 2018201069
//Name       : Neeraj Barthwal
#include "filetypeperm.h"

using namespace std;

bool is_directory(char *path){
	
	bool is_dir=false;
	struct stat pst;

	if(stat(path, &pst)==0 && S_ISDIR(pst.st_mode)){
		is_dir=true;
	}
	return is_dir;
}

bool is_regular_file(char *path){
	
	bool is_file=false;
	struct stat pst;

	if(stat(path, &pst)==0 && S_ISREG(pst.st_mode)){
		is_file=true;
	}
	return is_file;
}

vector<string> parse_file_name(string name){
	vector<string> input;// = split(name,' ');

	return input;
}

string convert_to_home(string dest){
		//Assume file name: ~/filename
		//Removing character ~ from destination
    	dest.erase(remove(dest.begin(), dest.end(), '~'), dest.end());
    	dest.erase(remove(dest.begin(), dest.end(), '/'), dest.end());
    	dest = HOME+"/"+dest;
    	return dest;
}

vector<string> split(const string& s, char delimiter)
{
   vector<string> tokens;
   string token;
   istringstream tokenStream(s);
   while (getline(tokenStream, token, delimiter))
   {
      tokens.push_back(token);
   }
   return tokens;
}
