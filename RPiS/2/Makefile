CPPFLAGS = -std=c++11 -Wall -Wextra
NAME = distribution
EXE =$(NAME).exe
SOURCES=$(NAME).cpp

.PHONY: run

$(EXE): $(SOURCES)
	g++ -o $@ $^ $(CPPFLAGS)

run: $(EXE)
	./$<
	gnuplot plot.gnu
	
tar: $(SOURCES) Makefile plot.gnu fnum.png fx.png porownanie.png
	tar -czvf PiotrGrudzienZestaw4Zad6.tar.gz $^