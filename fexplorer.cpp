#include <unistd.h>
#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <bits/stdc++.h>
#include <dirent.h>
#include <limits.h>
#include <termios.h>
#include <iomanip>
#include <vector>
#include <sys/ioctl.h>
#include "filetypeperm.h"

#define RESETCOLOR "\033[0m"
#define GREEN  "\e[32m"
#define BLUE_BG "\u001b[44m"
#define RESTORE_BG "\u001b[0m"
#define KEY_ESCAPE  0x001b
#define KEY_ENTER   0x000a
#define KEY_UP      0x0105
#define KEY_DOWN    0x0106
#define KEY_LEFT    0x0107
#define KEY_RIGHT   0x0108

#define cursor_up() printf("\033[1A")
#define cursor_down() printf("\033[1B")
using namespace std;

void gotoxy(int x,int y){
	printf("%c[%d;%df",0x1B,y,x);
}

void initialize_file_system_hierarchy(char *);
void do_listing();
void print_fs(unsigned int, int);
void initialize_file_explorer_tty();
void exit_file_explorer();
void reset_scroll_param();
void do_open(char[]);
void do_one_level_up();
void do_enter();
void clean_up_traversal(int);
void do_move_forward();
void do_move_backward();
void populate_traversal();
struct termios initial_settings, new_settings;
struct winsize win;
FILE *input, *output;
bool scrolling = false;
unsigned int pos_up=1, pos_down=1,bottom_of_screen,record_pointer=0, traversal_pointer=0;
vector<struct fileattr> fs_hierarchy;
vector<struct fileattr> fs_traversal;

string HOME;
int main(int argc, char *argv[]){
	
	char cwd[PATH_MAX];
	initialize_file_explorer_tty();

	if(argc!=2){

		 if(getcwd(cwd, sizeof(cwd))!=NULL){
                	initialize_file_system_hierarchy(cwd);
                	HOME=cwd;
                	struct fileattr homedir = fs_hierarchy[0];
                	homedir.f_path = trim_to_home(homedir.f_path);
                	fs_traversal.push_back(homedir);
       		 }else{
		 	cout<<"Error. Could not open PWD"<<"\n";
		 
		 }	
			
	}else{
	
		initialize_file_system_hierarchy(argv[1]);
	}

	char ch;
        do{
                ch=getchar();
		
		if (ch == '\033') { // if the first value is esc

   			 cin>>ch; // skip the [
			 cin>>ch;
    			 switch(ch) { // the real value
       				 case 'A':
					 //UP
					if(record_pointer==0){
						//already at the top of FS =>  NOP
						//pos_up=1;
						break;
					}
					record_pointer--;
					cursor_up();
					pos_up++;
					
					if(pos_down!=1)
            			pos_down--;
				//	cout<<"After up : pos up: "<<pos_up<<"pos_down: "<<pos_down<<"\n";
					if(pos_up>=win.ws_row){
						//clear screen
						 cout<<"\033[2J";
						 //move cursor to top left
						 gotoxy(0,0);
						 //print FS
						 print_fs(win.ws_row, (bottom_of_screen-(win.ws_row)));
						 gotoxy(0,0);
						 //reset down counter
						 pos_down=1;
				//		 cout<<"After up : pos up: "<<pos_up<<"pos_down: "<<pos_down<<"\n";

					}	

            		break;
       				 case 'B':
					//DOWN
				
					if(record_pointer==fs_hierarchy.size()-1){
						break;
					}
					record_pointer++;
					scrolling = true;
					pos_down++;
					if(pos_up!=1)
						pos_up--;
					cursor_down();
				//	cout<<"After down : pos up: "<<pos_up<<"pos_down: "<<pos_down<<"\n";
                    if(pos_down>=(win.ws_row)){
						// clear screen
                        cout<<"\033[2J";
						//move cursor to top
                        gotoxy(0,0);
						//print FS
                        print_fs(win.ws_row, (pos_down-(win.ws_row-1)));
						//move cursor back to the second last line of screen
						cout<<"\033[1A \033[1G";
						//reset pos_up counter.
						pos_up=1;
                                //		cout<<"After down : pos up: "<<pos_up<<"pos_down: "<<pos_down<<"\n";       
					}

					
           			 	break;
       				 case 'C':

           				
       				 	 do_move_forward();
           			 	 break;
       				 case 'D':
       				 	//cout<<"Left Arrow";
           				 do_move_backward();
           			 	 break;
   			 }
		}else if((int)ch==10){
			do_enter();	
		}else if((int)ch == 127){
			do_one_level_up();
		}

        }while(ch!='q');

	exit_file_explorer();
}

void do_move_forward(){
	auto it = fs_traversal.begin()+(traversal_pointer+1);
	if(it!=fs_traversal.end()){
		traversal_pointer++;
		string path = fs_traversal[traversal_pointer].f_path;
		char ab_path[PATH_MAX];
		strcpy(ab_path, path.c_str());
		cout<<"\033[2J";
		gotoxy(0,0);
		fs_hierarchy.clear();
		initialize_file_system_hierarchy(ab_path);

	}
}

void do_move_backward(){

	if(traversal_pointer>0){
		
		auto it = fs_traversal.begin()+(traversal_pointer-1);
		if(it!=fs_traversal.end()){
			traversal_pointer--;
			//cout<<"travel pointer: "<<traversal_pointer;
			string path = fs_traversal[traversal_pointer].f_path;
			//cout<<"path of file in traversal: "<<path;
			//int x; cin>>x;
			char ab_path[PATH_MAX];
			strcpy(ab_path, path.c_str());
			cout<<"\033[2J";
			gotoxy(0,0);
			fs_hierarchy.clear();
			initialize_file_system_hierarchy(ab_path);

		}
	}
}

void do_enter(){
	
	populate_traversal();

	char ab_path[PATH_MAX];
	string fpath = fs_hierarchy[record_pointer].f_path;
	strcpy(ab_path, fpath.c_str());
	//reset_scroll_param();
	//cout<<"\033[2J";
	//gotoxy(0,0);
	//fs_hierarchy.clear();
	do_open(ab_path);

}

void populate_traversal(){
	string f_name = fs_hierarchy[record_pointer].f_name;
	if(f_name=="."){
		return;
	}else if(f_name==".."){
		if(traversal_pointer>0){
			traversal_pointer--;
			clean_up_traversal(traversal_pointer+1);	
		}
		
	}else{
		//push to traversal tree
		fs_traversal.push_back(fs_hierarchy[record_pointer]);
		traversal_pointer++;
		//cout<<"B traversal size: "<<fs_traversal.size()<<" file inserted: "<<fs_traversal[traversal_pointer].f_name;
		//int x;cin>>x;
		//perform clean up
		clean_up_traversal(traversal_pointer+1);
		//cout<<"A traversal size: "<<fs_traversal.size()<<" file inserted: "<<fs_traversal[traversal_pointer].f_name;

		//cout<<"A traversal size: "<<fs_traversal.size();
		//int y;cin>>y;
	}
	
}

void clean_up_traversal(int index){
	fs_traversal.erase(fs_traversal.begin()+index,fs_traversal.end());
}


void do_open(char absolute_path[]){

	string type = fs_hierarchy[record_pointer].f_type;
	string name = fs_hierarchy[record_pointer].f_name;
	if(name=="."){
		gotoxy(4,0);
		reset_scroll_param();
	}else if(name==".."){
		string path = fs_hierarchy[record_pointer].f_path;
		string hpath = trim_to_home(path);

		if(hpath == HOME){
			gotoxy(4,0);
			reset_scroll_param();
		}else{
			path = trim_to_parent(path);
			char parent[PATH_MAX];
			strcpy(parent,path.c_str());
			reset_scroll_param();
			cout<<"\033[2J";
			gotoxy(0,0);
			fs_hierarchy.clear();
			initialize_file_system_hierarchy(parent);
		}

		
	}else{
			
			if(type[0]=='d'){
				reset_scroll_param();
				cout<<"\033[2J";
				fs_hierarchy.clear();
				gotoxy(0,0);
				initialize_file_system_hierarchy(absolute_path);
				return;
			}		
	}

}

void do_one_level_up(){

	traversal_pointer--;
	clean_up_traversal(traversal_pointer+1);
	
	string path = fs_hierarchy[record_pointer].f_path;
	string hpath = trim_to_home(path);
	
	if(hpath==HOME){
		gotoxy(4,0);
		reset_scroll_param();
	}else{

		path = trim_to_parent(path);
		char parent[PATH_MAX];
		strcpy(parent,path.c_str());
		cout<<"\033[2J";
		fs_hierarchy.clear();
		gotoxy(0,0);
		initialize_file_system_hierarchy(parent);
	}
	
}

void reset_scroll_param(){
	pos_down=1;
	pos_up=1;
	record_pointer=0;
}

/**
 * this function opens an alternate screen for the file explorer and sets the terminal to non-canonical mode.
 * new_settings represents the settings in non-canonical mode.
 * initial settings of the terminal are restored once the explorer exits through initial_settings
 * */
void initialize_file_explorer_tty(){

	cout<<"\033[?1049h\033[H";
        //cout<<"+*+*+*+*+*+*Awesome File Explorer*+*+*+*+*+*+*\n";

	//check if currently on terminal
        if(!isatty(fileno(stdout))){
                cerr<<"You are not on a terminal.\n";
        }

        input = fopen("/dev/tty","r");
        output = fopen("/dev/tty","w");

        if(!input|| !output){
                cerr<<"Unable to open /dev/tty\n";
        }

        tcgetattr(fileno(input), &initial_settings);
        new_settings = initial_settings;
        new_settings.c_lflag &= ~ICANON;
        new_settings.c_lflag &= ~ECHO;
        new_settings.c_cc[VMIN] = 1;
        new_settings.c_cc[VTIME] = 0;
        new_settings.c_lflag &= ~ISIG;

        if(tcsetattr(fileno(input), TCSANOW, &new_settings)!=0){
                cerr<<"Could not set attributes\n";
        }

}

/**
 *
 * this function performs long listing of the files and directories
 * */
void initialize_file_system_hierarchy(char *dir){

	struct dirent *dirp;
	DIR *dp = opendir(dir);

	string absolute(dir);
	absolute+="/";
	if(dp==NULL){
		cerr<<"Cannot open directory: "<<dir;
		return;
	}
	
	while( (dirp = readdir(dp))!=NULL )
	{
		string dname = dirp->d_name;
		string path = absolute+dname;
		struct fileattr myfile;
		//set file name
		myfile.f_name=dirp->d_name;
		//set file size
		stringstream stream;
		stream<<fixed<<setprecision(1)<<find_file_size((char*)path.c_str());
		myfile.f_size = stream.str()+"K";
		//set file owner
		myfile.f_owner=find_ownership((char*)path.c_str());
		//set file type and permissions
		myfile.f_type=find_file_type_permission((char*)path.c_str());
		//set file modified time
		myfile.f_time=find_file_mod_time((char*)path.c_str());
		//set file path
		myfile.f_path=path;
		fs_hierarchy.push_back(myfile);
		
	}
	
	do_listing();
	
}

void do_listing(){
	
	ioctl(STDOUT_FILENO, TIOCGWINSZ, &win);
	unsigned int window_size = win.ws_row;
	if(window_size<fs_hierarchy.size()){
		//scrolling = true;
	}
	print_fs(window_size,0);
	gotoxy(4,0);
}

void print_fs(unsigned int window_size, int offset){
	
	unsigned int i;
	//cout<<"OFFSET: "<<offset<<"\n";
	for(i=offset; i<(window_size+offset)-1 && (i<fs_hierarchy.size()) ;i++){
	

		
			cout<<left<<setw(4)<<i+1<<left<<setw(20)<<fs_hierarchy[i].f_name
                	<<left<<setw(10)<<fs_hierarchy[i].f_size
                	<<left<<setw(20)<<fs_hierarchy[i].f_owner
                	<<left<<setw(15)<<fs_hierarchy[i].f_type
                	<<left<<fs_hierarchy[i].f_time;
			//move cursor one line down and to the first column.
			cout<<"\033[1B \033[1G";
		
		
	}
	
	bottom_of_screen = i;
	
cout<<"\033[7m --Awesome File Explorer-- \033[m"<<" Bottom of screen: "<<bottom_of_screen<<" pos_down: "<<pos_down<<" pos_up: "<<pos_up<<" rp: "<<record_pointer;
}

string trim_to_parent(string parent){
	int found = 0;
	for(int i=parent.size()-1;i>=0;i--){
		if(parent[i]=='/'){
			found++;
			if(found==2){
				parent = parent.substr(0,i);
				break;
			}
			
		}
	}
	return parent;
}

string trim_to_home(string path){
	for(int i=path.size()-1;i>=0;i--){
		if(path[i]=='/'){
			path = path.substr(0,i);
			break;
		}
			
	}
	return path;
	
}

/**
 * this function restores the terminal to its initial settings via inital_settings
 * */
void exit_file_explorer(){

	tcsetattr(fileno(input),TCSANOW,&initial_settings);
	cout<<RESETCOLOR;
        cout<<"\033[?1049l"<<"\n";

}
