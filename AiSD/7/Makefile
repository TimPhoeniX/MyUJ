CPPFLAGS= -std=c++11 -Wall -Wextra
CC = g++
Name = test.exe
Sources= test.cpp
Headers= ctl_linkedlist.hpp ctl_forwardlist.hpp ctl_arraylist.hpp test.hpp
files= $(Sources) $(Headers) Makefile README
.PHONY: default run clean tar

default: $(Name)

$(Name): $(Sources) $(Headers)
	$(CC) -o $@ $(Sources) $(CPPFLAGS)

run: $(Name)
	./$<

clean:
	rm -rf *~
	rm -rf *.exe

tar: $(files)
	tar -czvf grudzienaisd5.tar.gz $^