CC=gcc
CFLAGS=-Wall -Wextra -O -fpic
LD=$(CC)
LFLAGS=-Wall -Wextra -O
AR=ar
ARFLAGS=rv
PROG1=multiprod
PROG1E=$(PROG1).exe
PROG2=multikons
PROG2E=$(PROG2).exe
PROG3=master
PROG3E=$(PROG3).exe
LIB1=semaphore
LIB1S=lib$(LIB1).a
LIB1D=lib$(LIB1).so
LIB2=sharedmem
LIB2S=lib$(LIB2).a
LIB2D=lib$(LIB2).so
LIBDIR=./lib
FILES= $(PROG1).c $(PROG2).c $(PROG3).c $(LIB1).c $(LIB1).h $(LIB2).c $(LIB2).h Makefile README

.PHONY: default run clean tar diff

%.o: %.c %.h
	$(CC) $(CFLAGS) -c $<
%.o: %.c
	$(CC) $(CFLAGS) -c $<


default: $(PROG1E) $(PROG2E) $(PROG3E2) $(PROG1E2) $(PROG2E2) $(PROG3E2) $(LIB1S) $(LIB1D) $(LIB2S) $(LIB2D)

$(PROG1E): $(PROG1).o $(LIB1D) $(LIB2D)
	$(CC) -o $@ $(CFLAGS) $< -l$(LIB1) -l$(LIB2) -L$(LIBDIR) -Wl,-R $(LIBDIR)

$(PROG2E): $(PROG2).o $(LIB1D) $(LIB2D)
	$(CC) -o $@ $(CFLAGS) $< -l$(LIB1) -l$(LIB2) -L$(LIBDIR) -Wl,-R $(LIBDIR)

$(PROG3E): $(PROG3).o $(LIB1D) $(LIB2D)
	$(CC) -o $@ $(CFLAGS) $< -l$(LIB1) -l$(LIB2) -L$(LIBDIR) -Wl,-R $(LIBDIR)

$(LIB1S): $(LIB1).o
	$(AR) $(ARFLAGS) $@ $?
	mkdir -p $(LIBDIR)
	mv $@ $(LIBDIR)

$(LIB1D): $(LIB1).o
	$(LD) $(LFLAGS) -shared -o $@ $^
	mkdir -p $(LIBDIR)
	mv $@ $(LIBDIR)

$(LIB2S): $(LIB2).o
	$(AR) $(ARFLAGS) $@ $?
	mkdir -p $(LIBDIR)
	mv $@ $(LIBDIR)

$(LIB2D): $(LIB2).o
	$(LD) $(LFLAGS) -shared -o $@ $^
	mkdir -p $(LIBDIR)
	mv $@ $(LIBDIR)

clean:
	rm -rf *~
	rm -rf *.exe
	rm -rf *.o
	rm -rf $(LIBDIR)

diff: source.txt copy.txt
	diff -s $^


run: $(PROG3E) $(PROG1E) $(PROG2E)
	rm -rf copy.txt
	./$< 600 300
	diff -s source.txt copy.txt

tar: $(FILES)
	tar -czvf sharedmemory.tar.gz $^