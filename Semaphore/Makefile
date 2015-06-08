CC=gcc
CFLAGS=-Wall -Wextra
PROG1=prog
PROG2=multiplier
LIB=semaphore
FILES=$(PROG1).c $(PROG2).c $(LIB).c $(LIB).h Makefile README

.PHONY: default run clean tar

default: $(PROG1).exe $(PROG2).exe

$(PROG1).exe: $(PROG1).c $(LIB).c $(LIB).h
	$(CC) -o $@ $(CFLAGS) $(PROG1).c $(LIB).c

$(PROG2).exe: $(PROG2).c $(LIB).c $(LIB).h
	$(CC) -o $@ $(CFLAGS) $(PROG2).c $(LIB).c


clean:
	rm -rf *~
	rm -rf *.exe

run: $(PROG2).exe $(PROG1).exe
	./$< 3

tar: $(FILES)
	tar -czvf semaphore.tar.gz $^