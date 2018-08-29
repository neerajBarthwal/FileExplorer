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

#endif

