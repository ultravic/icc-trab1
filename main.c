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

int main(int argc, char const *argv[]) {
  /* code */
  t_matrix matrix;

  matrix.matrix = (double *)malloc(sizeof(double));
  printf("N: ");
  scanf("%d", &matrix.lenght);

  matrix.matrix = generateSquareRandomMatrix(matrix.lenght);

  printMatrix(matrix);
  printf("\n");
  gaussElimination(&matrix);
  printMatrix(matrix);

  return 0;
}
