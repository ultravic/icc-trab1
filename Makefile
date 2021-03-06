CC = gcc
CFLAGS = -Wall -std=gnu89 -O1

vpath %.c src
vpath %.h headers

src = $(wildcard *.c)
OBJ = invmat.o printers.o matrix_generator.o matrix_solver.o gauss_elimination.o io.o

invmat: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

.PHONY: clean
clean:
	rm -f $(OBJ)
purge: clean
	rm -f invmat
