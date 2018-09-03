# FileExplorer

The application starts in Normal Mode and displays the contents of the CWD. To exit application press q. To switch to command mode press ':'. To swtich to normal mode from command mode press esc. 

Build Application: "make fexp"

The following assumptions have been made for the commands:

1. Copy : Expects atleast 2 arguments. Eg: copy <file1> <dir1> . It is also assumed that the directory to which files are being copied is valid and 	      exists prior to file copy.
 
	  Copy multiple files: copy file1 file2 file3 directory
	  Copy recursive     : copy -r dir1 dir2 (both dir1 and dir2 should be valid)


2. Create File: Expects atleast 2 arguments. Eg: copy <file1> <dir1> . dir1 should be a vaild directory. 

	To create file in the current working directory	: create file_name .
	To create file in a relative path              	: create file_name ~/directory
	Create with absolute path		       	: create file_name absploute_path_of_dir

3. Create Directory : Expects atleast 2 arguments. Eg: create_dir dir_name destination

	To create directory in the current working directory	: create_dir dir_name .
	To create dir in a relative path              		: create_dir dir_name ~/directory
	Create with absolute path		       		: create_dir dir_name absploute_path_of_dir

4. Delete File: Expects atleast 2 arguments. Eg: delete_file filename destination_of_file


	To delete in the current working directory		: delete_file filename .
	To del file in a relative path              		: delete_file filename ~/path_to_dir_of_file
	To delete file in absolute path				: delete_file filename absolute_path_of_dir_of_file

5. Delete Directory: Expects atleast 2 aguments. Eg: delete_dir dirname destination_of_dir

	To delete in the CWD	: delete_dir dirname .
	To delete in rel path	: delete_dir dirname ~/path_to_dir (eg: delete_dir mydir /home/user/os => deletes dir mydir in /home/user/os)
	To delete in abs path	: delete_dir dirname abs_path_to_dir

6. Rename File : rename absolute_path_with_old_name absolute_path_with_new_name eg: rename /home/user/os/file1.txt /home/user/os/file2.txt

7. Move File to dir	: move file1 file2 file3 <destination_directory> // directory should be a valid dir and should exist.
			: move -r dir1 dir2 (dir2 should be absolute path)

8. Goto a directory	: goto absolute_path_of_directory or goto / => takes you to home dir

9. snapshot		: snapshot <absolute path of directory to be snapped> <name of the dump file>. Dump file is create in the HOME of application.

10. search 		: search filename_with_extension 
	

 


