CPPFLAGS=-std=c++11 -Wall -Wextra
CC=g++
Name=bst
Sources=$(Name).cpp
Exe=$(Name).exe
Headers= ctl_bst.hpp
files= $(Sources) $(Headers) Makefile input.txt

.PHONY: default run clean tar

default: $(Exe)

$(Exe): $(Sources) $(Headers)
	$(CC) -o $@ $(Sources) $(CPPFLAGS)

run: $(Exe)
	./$<

clean:
	rm -rf *~
	rm -rf *.exe

tar: $(files)
	tar -czvf grudzienaisd9.tar.gz $^