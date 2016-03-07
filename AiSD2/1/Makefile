CPPFLAGS=-std=c++11 -Wall -Wextra
CC=g++
Name=set
Sources=main.cpp
Exe=$(Name).exe
Headers=ctl_set.hpp
Files= $(Sources) $(Headers) Makefile
.PHONY: default run clean tar

default: $(Exe)

$(Exe): $(Sources) $(Headers)
	$(CC) -o $@ $(Sources) $(CPPFLAGS)

run: $(Exe)
	./$< 

clean:
	rm -rf *~
	rm -rf *.exe
