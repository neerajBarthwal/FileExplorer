CC = g++
CFLAGS = -Wall -std=c++1z
DEPS = filetypeperm.h
OBJ = fileowner.o filesize.o filetime.o filetype.o fexplorer.o
%.o: %.cpp $(DEPS)
	$(CC) $(CFLAGS) -c -o $@ $<

fexp: $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

