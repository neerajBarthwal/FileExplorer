#include "filetypeperm.h"
using namespace std;
void switch_to_cmd_mode(){

	cout<<"\033[38;0H";
	cout<<"\033[2K";
	cout<<"\033[7m Command Mode:-- \033[m";
	char ch;
	string cmd="";
	do{
		ch = getchar();
		 
		
		if(ch==10){
			parse_cmd(cmd);
			cout<<"\033[2K";
			cout<<"\033[38;1H";
			cout<<"command mode :";
		}else if(ch==127){
			cout<<"\b \b";
			cmd.pop_back();
		}else{
			printf("%c",ch);
			cmd+=ch;
		}

	}while(ch!=27);

}

void parse_cmd(string cmd){
	cerr<<"\n"<<cmd;
	vector<string> cmdtoken = split(cmd,' ');

	if(cmdtoken.size()>=3){

		if(cmdtoken[0]=="copy"){

			if(cmdtoken[1]=="-r"){
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

		}else if(cmdtoken[0]=="create"){
			string destination = cmdtoken[cmdtoken.size()-1];
			if(destination==".")
				destination = CWD;
			else if(destination[0]=='~'){
				destination = convert_to_home(destination);
				replace(destination.begin(),destination.end(),'|',' ');
			}
			for(unsigned int i=1;i<cmdtoken.size()-1;i++){
				string path = destination+"/"+cmdtoken[i];
				create_file(path);
			}
		}else if(cmdtoken[0]=="create_dir"){
			string destination = cmdtoken[cmdtoken.size()-1];
			if(destination==".")
				destination = CWD;
			else if(destination[0]=='~'){
				destination = convert_to_home(destination);
				replace(destination.begin(),destination.end(),'|',' ');
			}
			for(unsigned int i=1;i<cmdtoken.size()-1;i++){
				string path = destination+"/"+cmdtoken[i];
				create_dir(path);
			}
		}else if(cmdtoken[0]=="delete_file"){
			string destination = cmdtoken[cmdtoken.size()-1];
			if(destination==".")
				destination = CWD;
			else if(destination[0]=='~'){
				destination = convert_to_home(destination);
				replace(destination.begin(),destination.end(),'|',' ');
			}
			for(unsigned int i=1;i<cmdtoken.size()-1;i++){
				string path = destination+"/"+cmdtoken[i];
				delete_file(path);
			}
		}else if(cmdtoken[0]=="delete_dir"){
			string destination = cmdtoken[cmdtoken.size()-1];
			if(destination==".")
				destination = CWD;
			else if(destination[0]=='~'){
				destination = convert_to_home(destination);
				replace(destination.begin(),destination.end(),'|',' ');
			}
			for(unsigned int i=1;i<cmdtoken.size()-1;i++){
				string path = destination+"/"+cmdtoken[i];
				delete_dir(path);
			}
		}else if(cmdtoken[0]=="rename"){
			string old_name = CWD+"/"+cmdtoken[1];
			string new_name = CWD+"/"+cmdtoken[2];
			rename_file(old_name,new_name);
			
		}else if(cmdtoken[0]=="move"){
			if(cmdtoken[1]=="-r"){
				string source_name = cmdtoken[2];
				string source_dir = CWD+"/"+source_name;
				string destination = cmdtoken[3];

				if(destination==".")
					destination = CWD;
				else if(destination[0]=='~'){
					destination = convert_to_home(destination);
					replace(destination.begin(),destination.end(),'|',' ');
				}
				cerr<<"source_name: "<<"source_dir: "<<source_dir<<"dest: "<<destination;
				move_dir_to_dir(source_name, source_dir,destination);
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
						move_files_to_dir(source,destination);
					}

			}

			
			
		}else if(cmdtoken[0]=="snapshot"){
			cerr<<"\n calling snapshot...";
			snapshot(cmdtoken[1],cmdtoken[2]);
		}


	}else if(cmdtoken[0]=="goto"){
			string destination = cmdtoken[1];
			if(destination=="/")
				destination=HOME;
			do_goto(destination);
		
	}else if(cmdtoken[0]=="search"){
		string filename = cmdtoken[1];
		string absolute_path = CWD;
		search(filename,absolute_path);
	}

}