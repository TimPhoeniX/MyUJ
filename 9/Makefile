CPPFLAGS= -std=c++11 -Wall -Wextra
CC = g++
Name=hashmap
Sources=$(Name).cpp
Exe=$(Name).exe
Headers= ctl_proto_hashmap.hpp test.hpp ctl_forwardlist.hpp
files= $(Sources1) $(Headers) Makefile README expressions.txt
.PHONY: default run1 run2 clean tar

default: $(Exe)

$(Exe): $(Sources) $(Headers)
	$(CC) -o $@ $(Sources) $(CPPFLAGS)

runt: $(Exe)
	./$< t

runm: $(Exe)
	./$< m < dane_nazwiska.txt > test.txt

clean:
	rm -rf *~
	rm -rf *.exe

tar: $(files)
	tar -czvf grudzienaisd7.tar.gz $^