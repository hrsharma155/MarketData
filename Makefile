CC=g++ #sets compiler to g++
CFLAGS=-std=c++11 #compilation options (use c++ 11 compiler)
LIBS=-lcurl #libraries to link (libcurl in this case)
LIBS+=-ljson-c -lssl #added json-c library to link against curl

#Object files
OBJ = test.o parse.o generalinfo.o

#Default target
all: test

#Compiles test.cpp to an object file
test.o: test.cpp
	$(CC) $(CFLAGS) -c test.cpp -o test.o

#Compiles parse.cpp to an object file
parse.o: Parse.cpp Parse.h
	$(CC) $(CFLAGS) -c Parse.cpp -o parse.o


#Compiles GeneralInfo.cpp to an object file
generalinfo.o: GeneralInfo.cpp GeneralInfo.h
	$(CC) $(CFLAGS) -c GeneralInfo.cpp -o generalinfo.o

#Links object files into the final executable
test: $(OBJ)
	$(CC) $(OBJ) -o test $(LIBS)

clean:
	rm -f $(OBJ) test





