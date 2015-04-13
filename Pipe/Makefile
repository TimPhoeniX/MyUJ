CC=gcc
CFLAGS=-Wall -Wextra
PROG1=pipe
# PROG2=
# PROG3=
FILES=$(PROG1).c $(PROG1).h Makefile README source.txt
# FILES=$(PROG1).c $(PROG2).c Makefile README
# FILES=$(PROG1).c $(PROG2).c $(PROG3).c Makefile README

.PHONY: default run clean tar

default: $(PROG1).exe
# default: $(PROG1).exe $(PROG2).exe
# default: $(PROG1).exe $(PROG2).exe $(PROG3).exe

$(PROG1).exe: $(PROG1).c $(PROG1).h
	$(CC) -o $@ $(CFLAGS) $(PROG1).c

# $(PROG2).exe: $(PROG2).c
# 	$(CC) -o $@ $(CFLAGS) $(PROG2).c
# 
# 
# $(PROG3).exe: $(PROG3).c
# 	$(CC) -o $@ $(CFLAGS) $(PROG3).c

clean:
	rm -rf *~
	rm -rf *.exe

run: $(PROG1).exe
	./$<

# run2: $(PROG2).exe
# 	./$<
# 
# run3: $(PROG3).exe
#	./$<
	
tar: $(FILES)
	tar -czvf pipe.tar.gz $^