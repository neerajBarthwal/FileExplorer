#include "filetypeperm.h"

using namespace std;

string convert_uid_toname(int);
string convert_gid_toname(int);

string find_ownership(char *dir){

	struct stat pst;

        if(lstat(dir,&pst)<0){
                cerr<<"FATAL:  Could not determine file permissions.";
                exit(1);
        }

	int uid = pst.st_uid;
	int gid = pst.st_gid;

	string user_name = convert_uid_toname(uid);
	string group_name = convert_gid_toname(gid);
	
	return user_name+"\t"+group_name;

}

string convert_uid_toname(int uid){
	struct passwd *pwd = getpwuid(uid);

	if(pwd==NULL){
		cerr<<"Could not fetch owner details: uid";
		return "";
	}else{
		return pwd->pw_name;
	}
		
}


string convert_gid_toname(int gid){

        struct group * grp = getgrgid(gid);
        if(grp==NULL){
                cerr<<"Could not fetch owner details: gid";
                return "";
        }else{
                return grp->gr_name;
        }

}


