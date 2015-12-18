STD=-std=c++11 -Wall

.PHONY: default 1 clean test
default: prog.exe

prog.exe: prog.cpp Miasto.cpp
	g++ $(STD) $^ -o $@
		
1: prog.exe
	./$<


clean:
	rm -rf *~
	rm -rf *.exe
