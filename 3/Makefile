.PHONY: tar clean run1 run2 run3 all

all: o1.exe o2.exe o3.exe

o1.exe: suma.cpp
	g++ $< -o $@ -std=c++11 -Wall -Wextra -O1

o2.exe: suma.cpp
	g++ $< -o $@ -std=c++11 -Wall -Wextra -O2

o3.exe: suma.cpp
	g++ $< -o $@ -std=c++11 -Wall -Wextra -O3

clean:
	rm -rf *~
	rm -rf *.exe

run1: o1.exe
	./$<

run2: o2.exe
	./$<

run3: o3.exe
	./$<

tar: Readme.txt Makefile suma.cpp
	tar -czvf grudzienaisd2.tar.gz $^