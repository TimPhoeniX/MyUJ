CPPFLAGS = -std=c++11
.PHONY: run

sort.exe: sort.cpp
	g++ -o $@ $^ $(CPPFLAGS)

run: sort.exe
	./$<