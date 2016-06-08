CPPFLAGS=-std=c++11 -Wall -Wextra
CC=g++
Name=main.exe
Sources=test.cpp
Headers=CTL/Graph/Graph.hpp CTL/Container/ctl_arraylist.hpp CTL/Sort/ctl_quick_sort.hpp CTL/Container/ctl_stack.hpp CTL/Utility/ctl_traits.hpp CTL/ctl_pair.hpp
Extra=Makefile
Files=$(Sources) $(Headers) $(Extra)

.PHONY: default runb rund clean tar Sample

default: $(Name)

$(Name): $(Sources) $(Headers)
	$(CC) -o $@ $(Sources) $(CPPFLAGS)

runb: $(Name)
	./$< -b A < test1.txt

rund: $(Name)
	./$< -d A < test1.txt

clean:
	rm -rf *~
	rm -rf *.exe

tar: $(Files)
	mkdir SP
	cp --parent $(Files) SP
	cp -r --parent CTL SP
	tar -czvf AiSD2-4-PiotrGrudzien.tar.gz SP
	rm -rf SP
