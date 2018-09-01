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
using namespace std;


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

int main(){

	string cmd;
	getline(cin,cmd);

	std::vector<string> cmdtoken = split(cmd,' ');

	if(cmdtoken[0]=="create"){
		for(unsigned int i=1;i<cmdtoken.size()-1;i++){
			string path = cmdtoken[cmdtoken.size()-1]+"/"+cmdtoken[i];
			create_file(path);
		}
	}


}

int create_file(string abs_path){

	int fd = open(abs_path, O_RDWR|O_CREAT, 0777);
	if (fd != -1) {
    	close(fd2);
	}
}