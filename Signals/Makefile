CC=gcc
CFLAGS=-Wall
PROG1=sig1
PROG2=sig2
FILES=$(PROG1).c $(PROG2).c Makefile README

.PHONY: default run clean tar

default: $(PROG1).exe $(PROG2).exe

$(PROG1).exe:
	$(CC) -o $@ $(CFLAGS) $(PROG1).c

$(PROG2).exe:
	$(CC) -o $@ $(CFLAGS) $(PROG2).c

clean:
	rm -rf *~
	rm -rf *.exe

run: $(PROG1).exe
	./$<

run2: $(PROG2).exe
	./$<

tar: $(FILES)
	tar -czvf fork.tar.gz $^