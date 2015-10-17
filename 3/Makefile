silnia.exe: silnia.cpp
	g++ $< -o $@ -std=c++11 -Wall -Wextra

.PHONY: clean run
clean:
	rm -rf *~
	rm -rf *.exe

run: silnia.exe
	./$< 

tar: Makefile main.cpp
	tar -czvf grudzienaisd2.tar.gz $^