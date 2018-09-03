CC = g++
CFLAGS = -Wall -std=c++1z
DEPS = filetypeperm.h
OBJ = fileowner.o filesize.o filetime.o filetype.o createfile.o createdir.o deletefile.o renamefile.o move.o cmdmode.o fileutil.o search.o snapshot.o copyfile.o fexplorer.o
%.o: %.cpp $(DEPS)
	$(CC) $(CFLAGS) -c -o $@ $<

fexp: $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

