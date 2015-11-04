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
	diff -q stable_sorted.txt unstable_sorted.txt

clean:
	rm -rf *~
	rm -rf *.exe
	rm -rf *_sorted.txt

tar: $(files)
	tar -czvf grudzienaisd4.tar.gz $^