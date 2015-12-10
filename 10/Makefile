CPPFLAGS=-std=c++11 -Wall -Wextra
CC=g++
Name=openmap
Sources=$(Name).cpp
Exe=$(Name).exe
Headers= ctl_open_map.hpp
files= $(Sources) $(Headers) Makefile dane_nazwiska.txt
.PHONY: default run0 run1 run2 clean tar

default: $(Exe)

$(Exe): $(Sources) $(Headers)
	$(CC) -o $@ $(Sources) $(CPPFLAGS)

run0: $(Exe)
	./$< 501 0 < dane_nazwiska.txt

run1: $(Exe)
	./$< 501 1 < dane_nazwiska.txt

run2: $(Exe)
	./$< 501 2 < dane_nazwiska.txt

clean:
	rm -rf *~
	rm -rf *.exe

tar: $(files)
	tar -czvf grudzienaisd8.tar.gz $^