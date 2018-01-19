CPPFLAGS=-std=c++11 -Wall -Wextra -pedantic
CC=g++-6
Name=uj_list.exe
Sources=main.cpp
Headers=uj_list.hpp
Extra=Makefile
Files=$(Sources) $(Headers) $(Extra)

.PHONY: default run clean tar

default: $(Name)

$(Name): $(Sources) $(Headers)
	$(CC) -o $@ $(Sources) $(CPPFLAGS) -lcppunit -D_GLIBCXX_USE_CXX11_ABI=0

run: $(Name)
	./$<

clean:
	rm -rf *~
	rm -rf *.exe

tar: $(Files)
	mkdir Lista
	cp --parent $(Files) Lista
	cp -r --parent Doxygen Lista
	tar -czvf ListaPiotrGrudzien.tar.gz Lista
	rm -rf Lista
