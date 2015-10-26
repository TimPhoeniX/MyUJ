CPPFLAGS= -std=c++11 -Wall -Wextra
.PHONY: clean run tar run10 run11 run20 run21 run30 run31 runall

sort.exe: sort.cpp
	g++ $(CPPFLAGS) -o $@ $^

run: sort.exe
	./$<

clean:
	rm -rf *~
	rm -rf *.exe

run10: sort.exe
	./$< 1 0 < dane_duze.txt > moje_wyniki.txt
	diff -s wyniki_duze.txt moje_wyniki.txt

run11: sort.exe
	./$< 1 1 < dane_duze.txt > moje_wyniki.txt
	diff -s wyniki_duze_rosnaco.txt moje_wyniki.txt

run20: sort.exe
	./$< 2 0 < dane_duze.txt > moje_wyniki.txt
	diff -s wyniki_duze.txt moje_wyniki.txt

run21: sort.exe
	./$< 2 1 < dane_duze.txt > moje_wyniki.txt
	diff -s wyniki_duze_rosnaco.txt moje_wyniki.txt

run30: sort.exe
	./$< 1 0 < dane_duze.txt > moje_wyniki.txt
	diff -s wyniki_duze.txt moje_wyniki.txt

run31: sort.exe
	./$< 1 1 < dane_duze.txt > moje_wyniki.txt
	diff -s wyniki_duze_rosnaco.txt moje_wyniki.txt

runall: sort.exe
	make run10
	make run11
	make run20
	make run21
	make run30
	make run31

tar: sort.cpp Makefile dane_duze.txt wyniki_duze.txt wyniki_duze_rosnaco.txt
	tar -czvf grudzienaisd3.tar.gz $^