CC=gcc
CFLAGS=-Wall -Wextra
PROG1=producent
PROG2=konsument
PROG3=pipe
FILES=$(PROG1).c $(PROG2).c $(PROG3).c $(PROG3).h Makefile README source.txt

.PHONY: default run clean tar

default: $(PROG1).exe $(PROG2).exe

$(PROG1).exe: $(PROG1).c $(PROG3).c $(PROG3).h
	$(CC) -o $@ $(CFLAGS) $< $(PROG3).c

$(PROG2).exe: $(PROG2).c $(PROG3).c $(PROG3).h
	$(CC) -o $@ $(CFLAGS) $< $(PROG3).c

mypipe:
	mkfifo -m 0644 mypipe

clean:
	rm -rf *~
	rm -rf *.exe
	rm -rf mypipe

run: $(PROG1).exe
	./$<

run2: $(PROG2).exe
	./$<

tar: $(FILES)
	tar -czvf fifo.tar.gz $^