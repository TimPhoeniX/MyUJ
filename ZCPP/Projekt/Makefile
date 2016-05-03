CPPFLAGS=-std=c++11 -Wall -Wextra -pedantic
CC=g++
Name=uj_list.exe
Sources=main.cpp
Headers=uj_list.hpp
Extra=Makefile
Files=$(Sources) $(Headers) $(Extra)

.PHONY: default run clean tar

default: $(Name)

$(Name): $(Sources) $(Headers)
	$(CC) -o $@ $(Sources) $(CPPFLAGS)

run: $(Name)
	./$<

clean:
	rm -rf *~
	rm -rf *.exe

tar: $(Files)
	mkdir Lista
	cp --parent $(Files) List
	tar -czvf ListaPiotrGrudzien.tar.gz Lista
	rm -rf List
