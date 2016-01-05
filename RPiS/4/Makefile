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