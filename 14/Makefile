CC=g++
CPPFLAGS=-Wall -Wextra -std=c++11 -fopenmp
PROG1=main
LIB1=octree
LIB2=obj

.PHONY: default run plot plot2 plot3 clean display display2

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

plot: plot.gnu plot.txt
	gnuplot -p $<
	
plot2: plot2.gnu plot.txt 
	gnuplot -p $<

plot3: plot3d.gnu plot.txt
	gnuplot -p $<

plot4: plot4d.gnu plot.txt
	gnuplot -p $<

plot.txt:
	make run

plot.svg: plot.gnu plot.txt
	gnuplot $<

display: plot.svg
	eog $<