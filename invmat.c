#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "headers/gauss_elimination.h"
#include "headers/matrix_generator.h"
#include "headers/datatypes.h"
#include "headers/printers.h"
#include "headers/io.h"

int main(int argc, char const *argv[])
{
	char *file;
	if (!argv[1]) {
		file = "stdin";
	} else {
		file = (char *)argv[1];
	}

	t_matrix *matrix;
	t_matrix matrixL;
	INIT_MATRIX(matrix);

	if(readMatrix(matrix,file) == ERROR){
		printf("Erro! Não foi possível ler a entrada.\n");
		return ERROR;
	}

	matrix.matrix = generateSquareRandomMatrix(matrix.lenght);

	printMatrix(matrix);
  printf("\n");
  matrixL = gaussElimination(&matrix);
  printMatrix(matrix);
  printf("\n");
  printMatrixL(matrixL);

	return SUCCESS;
}
