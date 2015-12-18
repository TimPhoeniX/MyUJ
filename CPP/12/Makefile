CC=g++
CPPFLAGS=-Wall -Wextra -std=c++11
PROG1=main
LIB1=octree
LIB2=obj

.PHONY: default run clean

default: $(PROG1).exe

$(PROG1).exe: $(PROG1).cpp $(LIB1).cpp $(LIB1).hpp $(LIB2).cpp $(LIB2).hpp
	$(CC) -o $@ $(CPPFLAGS) $(PROG1).cpp $(LIB2).cpp

clean:
	rm -rf *~
	rm -rf *.exe

run: $(PROG1).exe
	./$<
