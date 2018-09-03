#include "filetypeperm.h"
using namespace std;

/*string HOME="/home/neeraj/project/OS/fileexplorer/code";
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
}*/

int create_file(string abs_path){

	int fd = open(abs_path.c_str(), O_RDWR|O_CREAT, 0777);
	if (fd != -1) {
    	close(fd);
	}
	return fd;
}

/*int main(){

	string cmd;
	getline(cin,cmd);

	std::vector<string> cmdtoken = split(cmd,' ');

	if(cmdtoken[0]=="create"){
		for(unsigned int i=1;i<cmdtoken.size()-1;i++){
			string path = cmdtoken[cmdtoken.size()-1]+"/"+cmdtoken[i];
			create_file(path);
		}
	}


}*/

