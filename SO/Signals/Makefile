CC=gcc
CFLAGS=-Wall
PROG1=sig1
PROG2=sig2
PROG3=sig3
FILES=$(PROG1).c $(PROG2).c $(PROG3).c Makefile README

.PHONY: default run clean tar

default: $(PROG1).exe $(PROG2).exe $(PROG3).exe

$(PROG1).exe: $(PROG1).c
	$(CC) -o $@ $(CFLAGS) $(PROG1).c

$(PROG2).exe: $(PROG2).c
	$(CC) -o $@ $(CFLAGS) $(PROG2).c


$(PROG3).exe: $(PROG3).c
	$(CC) -o $@ $(CFLAGS) $(PROG3).c

clean:
	rm -rf *~
	rm -rf *.exe

run: $(PROG1).exe
	./$<

run2: $(PROG2).exe
	./$<

run3: $(PROG3).exe
	./$<
	
tar: $(FILES)
	tar -czvf signals.tar.gz $^