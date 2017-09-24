CC = gcc
CFLAGS = -Wall -std=gnu89 -O1 -g -lrt
DEBUG =

vpath %.c src
vpath %.h lib

src = $(wildcard *.c)
OBJ = invmat.o matrix_generator.o matrix_solver.o partial_pivoting.o result_refinement.o gauss_elimination.o io.o time_measurement.o error_handler.o

invmat: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)
doc: FORCE
	doxygen doc/config
	ln -rsf doc/doxyfiles/html/index.html doc.html
FORCE:
clean_doc:
	rm -rf doc/doxyfiles/* doc.html
clean: clean_doc
	rm -f $(OBJ)
purge: clean
	rm -f invmat
