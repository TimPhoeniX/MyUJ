CPPFLAGS=-std=c++11 -Wall -Wextra
CC=g++
Name=sort
Executable=$(Name).exe
Sources=$(Name).cpp
Headers=ctl_data.hpp ctl_pair.hpp ctl_sort.hpp
files=$(Sources) $(Headers) Makefile dane.txt README 

.PHONY: default run clean tar

default: $(Executable)

$(Executable): $(Sources) $(Headers)
	$(CC) -o $@ $(Sources) $(CPPFLAGS)

run: $(Executable)
	./$<

clean:
	rm -rf *~
	rm -rf *.exe

tar: $(files)
	tar -czvf grudzienaisd4.tar.gz $^