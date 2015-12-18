CPPFLAGS= -std=c++11 -Wall -Wextra
CC = g++
Name = run.exe
Sources= run.cpp
Headers= ctl_matrix.hpp  

.PHONY: default run clean tar

default: $(Name)

$(Name): $(Sources) $(Headers)
	$(CC) -o $@ $(Sources) $(CPPFLAGS)

run: $(Name)
	./$< < matrices.txt > results.txt

clean:
	rm -rf *~
	rm -rf *.exe