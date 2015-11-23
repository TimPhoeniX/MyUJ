CPPFLAGS= -std=c++11 -Wall -Wextra
CC = g++
Name = test.exe
Sources= test.cpp
<<<<<<< HEAD
Headers= ctl_forwardlist.hpp ctl_stack.hpp
=======
Headers= ctl_stack.hpp ctl_rpn.hpp test.hpp
>>>>>>> cb9da067ee3a27249121753d9152b22fd2ea4b89
files= $(Sources) $(Headers) Makefile README
.PHONY: default run clean tar

default: $(Name)

$(Name): $(Sources) $(Headers)
	$(CC) -o $@ $(Sources) $(CPPFLAGS)

run: $(Name)
	./$<

clean:
	rm -rf *~
	rm -rf *.exe