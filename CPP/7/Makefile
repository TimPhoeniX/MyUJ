CC=g++
CPPFLAGS=-Wall -Wextra -std=c++11
PROG1=prog
LIB1=Vehicles
.PHONY: default run clean

default: $(PROG1).exe

$(PROG1).exe: $(PROG1).cpp $(LIB1).cpp $(LIB1).hpp
	$(CC) -o $@ $(CPPFLAGS) $(PROG1).cpp $(LIB1).cpp

clean:
	rm -rf *~
	rm -rf *.exe

run: $(PROG1).exe
	./$<
