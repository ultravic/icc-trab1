#include <stdio.h>
#include <stdlib.h>
#include "processors/gauss_elimination.h"
#include "generator/matrix_generator.h"
#include "datatypes.h"

void printMatrix(t_matrix matrix)
{
  int i, j;
  for (i = 0; i < matrix.lenght; ++i) {
    for (j = 0; j < matrix.lenght; ++j) {
      printf("%lf ", matrix.matrix[i*matrix.lenght + j]);
    }
    printf("\n");
  }
}

void printMatrixL(t_matrix matrix)
{
  int i;
  printf("%d\n", matrix.lenght);
  for (i = 0; i < matrix.lenght; ++i) {
    printf("%1.20f\n", matrix.matrix[i]);
  }
}

int main(int argc, char const *argv[]) {
  /* code */
  t_matrix matrix;
  t_matrix matrixL;

  matrix.matrix = (double *)malloc(sizeof(double));
  printf("N: ");
  //scanf("%d", &matrix.lenght);
  matrix.lenght = 4;

  matrix.matrix = generateSquareRandomMatrix(matrix.lenght);

  printMatrix(matrix);
  printf("\n");
  matrixL = gaussElimination(&matrix);
  printMatrix(matrix);
  printf("\n");
  printMatrixL(matrixL);

  return 0;
}
