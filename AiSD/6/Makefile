CPPFLAGS= -std=c++11 -Wall -Wextra
.PHONY: clean run tar

sort.exe: sort.cpp
	g++ $(CPPFLAGS) -o $@ $^

clean:
	rm -rf *~
	rm -rf *.exe

run: sort.exe
	./$< < dane.txt > moje_wyniki.txt
	diff -s wyniki.txt moje_wyniki.txt

tar: sort.cpp Makefile dane_duze.txt wyniki_duze.txt wyniki_duze_rosnaco.txt
	tar -czvf grudzienaisd3.tar.gz $^