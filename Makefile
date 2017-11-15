CC = gcc
CFLAGS = -Wall -lrt -lm
DEBUG = -DDEBUG -g

vpath %.c src
vpath %.h lib

src = $(wildcard *.c)
OBJ = invmat.o matrix_generator.o matrix_solver.o partial_pivoting.o result_refinement.o gauss_elimination.o io.o time_measurement.o error_handler.o

all: invmat
invmat: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)
debug: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(DEBUG)

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
	# -DLIKWID_PERFMON -I<PATH_TO_LIKWID>/include
	#  -L<PATH_TO_LIKWID>/lib -llikwid