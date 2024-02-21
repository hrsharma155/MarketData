CC=g++ #sets compiler to g++
CFLAGS=-std=c++11 #compilation options (use c++ 11 compiler)
LIBS=-lcurl #libraries to link (libcurl in this case)
LIBS+=-ljson-c -lssl #added json-c library to link against curl

test: test.cpp #target test depends on test.cpp
	$(CC) $(CFLAGS) test.cpp -o test $(LIBS) 