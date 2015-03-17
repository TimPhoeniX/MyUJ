STD=-std=c++11

.PHONY: default 1 2 3 clean
default: prog1.exe prog2.exe prog3.exe

prog1.exe: prog1.cpp
	g++ $(STD) $^ -o $@

prog2.exe: prog2.cpp
	g++ $(STD) $^ -o $@

prog3.exe: prog3.cpp
	g++ $(STD) $^ -o $@
1: prog1.exe
	./$< 10
2: prog2.exe
	./$<
3: prog3.exe
	./$< 10

clean:
	rm -rf *~
	rm -rf *.exe