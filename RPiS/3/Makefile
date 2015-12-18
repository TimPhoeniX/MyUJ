CPPFLAGS = -std=c++11 -Wall -Wextra
NAME = poisson
EXE =$(NAME).exe
SOURCES=$(NAME).cpp

.PHONY: run tar clean plot

$(EXE): $(SOURCES)
	g++ -o $@ $^ $(CPPFLAGS)

run: $(EXE)
	./$<
	gnuplot plot.gp

plot: results.txt
	gnuplot plot.gp

clean:
	rm -rf *~
	rm -rf *.exe

tar: $(SOURCES) Makefile plot.gp fnum.png fx.png porownanie.png results.txt
	tar -czvf PiotrGrudzienZestaw5Zad1.tar.gz $^