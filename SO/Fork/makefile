.PHONY: default clean run tar
default: fork.exe

fork.exe: fork.c
	gcc $^ -o $@

clean:
	rm -rf *~
	rm -rf *.exe

run: fork.exe
	./fork.exe

tar: README Makefile fork.c
	tar -czvf fork.tar.gz $^