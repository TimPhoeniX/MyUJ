binsearch.exe: main.cpp
	g++ $< -o $@ -std=c++14

.PHONY: clean run
clean:
	rm -rf *~
	rm -rf *.exe

run: binsearch.exe
	./$< < dane.txt > wyniki.txt
	diff -s wyniki.txt przykl_wyniki.txt

tar: Makefile main.cpp
	tar -czvf grudzienaisd1.tar.gz $^