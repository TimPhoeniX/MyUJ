CPPFLAGS= -std=c++11 -Wall -Wextra
CC = g++
Name = sort.exe
Sources= sort.cpp
Headers= ctl_data.hpp
files= $(Sources) ctl_data.hpp Makefile dane.txt wyniki_stable.txt  

.PHONY: default run clean tar

default: $(Name)

$(Name): $(Sources)
	$(CC) -o $@ $(Sources) $(CPPFLAGS)

run: $(Name)
	./$<

clean:
	rm -rf *~
	rm -rf *.exe