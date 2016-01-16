CPPFLAGS = -std=c++11 -Wall -Wextra
NAME = chi
EXE =$(NAME).exe
SOURCES=$(NAME).cpp

.PHONY: run

$(EXE): $(SOURCES)
	g++ -o $@ $^ $(CPPFLAGS)

run: $(EXE)
	./$<
	gnuplot plot.gp
	eog porownanie.png

clean:
	rm -rf *~
	rm -rf *.exe

tar: $(SOURCES) Makefile plot.gp porownanie.png results.txt
	tar -czvf PiotrGrudzienZestaw7Zad1.tar.gz $^