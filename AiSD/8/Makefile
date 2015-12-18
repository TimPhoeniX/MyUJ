CPPFLAGS= -std=c++11 -Wall -Wextra
CC = g++
Name1= calculate.exe
Sources1= calculate.cpp
Name2= rpniser.exe
Sources2= rpniser.cpp
Headers= ctl_stack.hpp test.hpp ctl_forwardlist.hpp
files= $(Sources1) $(Sources2) $(Headers) Makefile README expressions.txt
.PHONY: default run1 run2 clean tar

default: $(Name)

$(Name1): $(Sources1) $(Headers)
	$(CC) -o $@ $(Sources1) $(CPPFLAGS)

$(Name2): $(Sources2) $(Headers)
	$(CC) -o $@ $(Sources2) $(CPPFLAGS)
	
run1: $(Name1)
	./$<

run2: $(Name2)
	./$< < expressions.txt

run3: $(Name1) $(Name2)
	./$(Name2) < expressions.txt | ./$(Name1) > results.txt

clean:
	rm -rf *~
	rm -rf *.exe

tar: $(files)
	tar -czvf grudzienaisd6.tar.gz $^