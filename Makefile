CC=gcc
CFLAGS = -Wall -std=gnu89 -O1
INCLDIR = ./headers
INCL = -I$(INCLDIR)
DEPS = $(INCLDIR)/*
OBJ=invmat.o io.o
all: invmat
invmat: $(OBJ)
	$(CC) $(CFLAGS) $^ -o $@
invmato.o: $(DEPS) io.o
io.o: $(DEPS)
clean:
	rm -f $(OBJ)
purge: clean
	rm -f invmat
