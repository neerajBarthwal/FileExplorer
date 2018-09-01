#include "filetypeperm.h"
using namespace std;
void switch_to_cmd_mode(){

	cout<<"\033[38;5H";
	cout<<"\033[7m --Command Mode: -- \033[m";
	char ch;
	string cmd="";
	do{
		ch = getchar();
		printf("%c",ch); 
		cmd+=ch;
		if(ch==10){
			parse_cmd(cmd);
		}

	}while(ch!=27);

}

void parse_cmd(string cmd){

	vector<string> cmdtoken = split(cmd,' ');

	if(cmdtoken.size()>=3){

		if(cmdtoken[0]=="copy"){

			if(cmdtoken[1]=="-r"){
				cout<<cmdtoken[2]<<" : "<<CWD+"/"+cmdtoken[2]<<" : "<<cmdtoken[3];

				copy_dir_to_dir(cmdtoken[2],CWD+"/"+cmdtoken[2],cmdtoken[3]);
			}else{

					for(unsigned int i=1;i<cmdtoken.size()-1;i++){
						string source = cmdtoken[i];
						if(source[0]=='~'){
							source = convert_to_home(source);
							replace(source.begin(),source.end(),'|',' ');
						}else{
							replace(source.begin(),source.end(),'|',' ');
							source = CWD+"/"+source;
						}
						string destination = cmdtoken[cmdtoken.size()-1];
						if(destination[0]=='~' && destination[1]=='/'){
							destination = convert_to_home(destination);
						}
						destination+="/"+cmdtoken[i];
						copy_files_to_dir(source,destination);
					}

				}

		}

	}

}