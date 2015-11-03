CPPFLAGS= -std=c++11 -Wall -Wextra
CC = g++
Name = sort.exe
Sources= sort.cpp
Headers= ctl_data.hpp ctl_pair.hpp ctl_sort.hpp
files= $(Sources) $(Headers) Makefile dane.txt README 

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
	tar -czvf grudzienaisd3.tar.gz $^