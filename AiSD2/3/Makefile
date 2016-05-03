CPPFLAGS= -std=c++11 -Wall -Wextra
CC = g++
Name = cc.exe
Sources= aisd2-1.cpp
Headers= ctl_virtual_disjointset.hpp

.PHONY: default runt runl clean tar

default: $(Name)

$(Name): $(Sources) $(Headers)
	$(CC) -o $@ $(Sources) $(CPPFLAGS)

runl: $(Name)
	./$< l < alg.txt
	
runt: $(Name)
	./$< t < alg.txt

clean:
	rm -rf *~
	rm -rf *.exe