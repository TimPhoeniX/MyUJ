CPPFLAGS= -std=c++11 -Wall -Wextra
.PHONY: clean run tar

sort.exe: sort.cpp
	g++ $(CPPFLAGS) -o $@ $^

run: sort.exe
	./$<

run20: sort.exe
	./$< 2 0 < dane_duze.txt > moje_wyniki.txt
	diff -s wyniki_duze_rosnaco.txt moje_wyniki.txt

run21: sort.exe
	./$< 2 1 < dane_duze.txt > moje_wyniki.txt
	diff -s wyniki_duze.txt moje_wyniki.txt