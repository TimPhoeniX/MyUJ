.PHONY: default clean run tar

default: execl.exe ids.exe

ids.exe: ids.c
	gcc $^ -o $@ -Wall
execl.exe: execl.c
	gcc $^ -o $@ -Wall

clean:
	rm -rf *~
	rm -rf *.exe

run: execl.exe ids.exe
	./$<

tar: README Makefile execl.c ids.c
	tar -czvf execl.tar.gz $^