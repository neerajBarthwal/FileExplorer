#include <string>
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
#include <unistd.h>
#include <vector>
#include <algorithm>
#include <sstream>
#include <fcntl.h>
#include <sys/stat.h>
#include <dirent.h>
#ifndef filetypeperm_H
#define filetypeperm_H

struct fileattr{
	std:: string f_name;
	std:: string f_size;
	std:: string f_owner;
	std:: string f_type;
	std:: string f_time;
	std:: string f_path;

};

extern std::string HOME;
extern std::string CWD;
extern std::vector<struct fileattr> fs_search;

std::string find_file_type_permission(char *);
std::string find_type(int);
std::string find_permission(int);
float find_file_size(char *dir);
std::string find_ownership(char *dir);
std::string conver_uid_toname(int);
std::string convert_gid_toname(int);
std::string find_file_mod_time(char *dir);
std::string trim_to_parent(std::string);
std::string trim_to_home(std::string);


//util functions
bool is_directory(char *path);
bool is_regular_file(char *path);
std::vector<std::string> parse_file_name(std::string name);
std::string convert_to_home(std::string dest);

//Command mode functions
void switch_to_cmd_mode();
std::vector<std::string> split(const std::string& s, char delimiter);
void parse_cmd(std::string cmd);

//copy functions
int copy_files_to_dir(std::string source, std::string destination);
void copy_dir_to_dir(std::string source_name, std::string source_path, std::string destination);

//create file
int create_file(std::string abs_path);

//create dir
void create_dir(std::string abs_path);

//delete_file
void delete_file(std::string abs_path);
void delete_dir(std::string abs_path);

//rename
void rename_file(std::string old_name, std::string new_name);

//move
void move_dir_to_dir(std::string source, std::string source_dir, std::string desination);
void move_files_to_dir(std::string source, std::string destination);

//goto
void do_goto(std::string path);

//search
void search(std::string filename, std::string absolute_path);
void display_search_result();

//snapshot
void snapshot(std::string source, std::string destination);
void do_snap(std::string source);
#endif

