CC=g++
CPPFLAGS=-Wall -Wextra -std=c++11 -fopenmp
PROG1=main
LIB1=octree
LIB2=obj

.PHONY: default run run2 plot clean display

default: $(PROG1).exe

$(PROG1).exe: $(PROG1).cpp $(LIB1).cpp $(LIB1).hpp $(LIB2).cpp $(LIB2).hpp
	$(CC) -o $@ $(CPPFLAGS) $(PROG1).cpp $(LIB2).cpp

clean:
	rm -rf *~
	rm -rf *.exe
	rm -rf *.svg
	rm -rf plot.txt

run: $(PROG1).exe
	./$<

run2: $(PROG1).exe
	make run
	make plot
	make display
	
plot: plot.txt
	gnuplot plot.gnu

plot.txt:
	make run

plot.svg: plot.txt plot.gnu
	make plot

display: plot.svg
	eog $<