CC=gcc
CFLAGS=-Wall -Wextra
PROG1=main
PROG2=pipe
FILES=$(PROG1).c $(PROG2).c $(PROG2).h Makefile README source.txt

.PHONY: default run clean tar

default: $(PROG1).exe

$(PROG1).exe: $(PROG1).c $(PROG2).c $(PROG2).h
	$(CC) -o $@ $(CFLAGS) $(PROG1).c $(PROG2).c

clean:
	rm -rf *~
	rm -rf *.exe

run: $(PROG1).exe
	./$<

tar: $(FILES)
	tar -czvf pipe.tar.gz $^