CPPFLAGS = -std=c++11 -Wall -Wextra
.PHONY: run

pi.exe: pi.cpp
	g++ -o $@ $^ $(CPPFLAGS)

run: pi.exe
	./$<