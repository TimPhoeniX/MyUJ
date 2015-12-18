CC=gcc
CFLAGS=-Wall -Wextra -O -fpic
LD=$(CC)
LFLAGS=-Wall -Wextra -O
AR=ar
ARFLAGS=rv
PROG1=serwer
PROG1E=$(PROG1).exe
PROG2=klient
PROG2E=$(PROG2).exe
LIB1=mqueues
LIB1D=lib$(LIB1).so
LIBDIR=.
FILES=$(PROG1).c $(PROG2).c $(LIB1).c $(LIB1).h Makefile README

.PHONY: default run clean tar diff

%.o: %.c %.h
	$(CC) $(CFLAGS) -c $<
%.o: %.c
	$(CC) $(CFLAGS) -c $<

default: $(PROG1E)  $(PROG2E) $(LIB1D)

$(PROG1E): $(PROG1).o $(LIB1D)
	$(CC) -o $@ $(CFLAGS) $< -l$(LIB1) -L$(LIBDIR) -Wl,-R ./
 
$(PROG2E): $(PROG2).o $(LIB1D)
	$(CC) -o $@ $(CFLAGS) $< -l$(LIB1) -L$(LIBDIR) -Wl,-R ./


$(LIB1D): $(LIB1).o
	$(LD) $(LFLAGS) -shared -o $@ $^

clean:
	rm -rf *~
	rm -rf *.exe
	rm -rf *.o

run: $(PROG1E) $(PROG2E)
	xterm -hold -T Serwer -e ./$(PROG1E) &
	xterm -lc -hold -T Klient1 -e ./$(PROG2E) pierwszy_napis &
	xterm -lc -hold -T Klient2 -e ./$(PROG2E) drugi_napis &
	xterm -lc -hold -T Klient3 -e ./$(PROG2E) trzeci_napis &
	xterm -lc -hold -T Klient4 -e ./$(PROG2E) czwarty_napis &

tar: $(FILES)
	tar -czvf messagequeues.tar.gz $^