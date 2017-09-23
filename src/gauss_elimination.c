#include <stdio.h>
#include <stdlib.h>
#include "../headers/gauss_elimination.h"
#include "../headers/partial_pivoting.h"
#include "../headers/datatypes.h"

/*
    - Função criada para fazer a troca de linhas.
    - Recebe um vetor, seu tamanho e as duas linhas
   a serem trocadas.
*/
void changeLines(t_matrix *matrix, int fline, int sline)
{
  int i;
  double temporary;
  int length = matrix->length;

  for (i = 0; i < length; ++i) {
    temporary = matrix->matrix[(fline*length) + i];
    matrix->matrix[(fline*length) + i] = matrix->matrix[(sline*length) + i];
    matrix->matrix[(sline*length) + i] = temporary;
  }
}

void initMatrixL(t_matrix *matrixL, int length)
{
  int i, sizeL = 0;
  i = length - 1;

  while (i) {
    sizeL += i;
    --i;
  }

  matrixL->length = sizeL;
  matrixL->matrix = ALLOC(double, sizeL);
}

/*
    - Função que utiliza o método da eliminação de Gauss.
    - Recebe um vetor e seu tamanho.''
*/
void gaussElimination(t_matrix *matrix, t_matrix *matrixL, int *index_array)
{
    int j, i, k, sizeL = 0;
    int length = matrix->length;

    for (i = 0; i < (length - 1); ++i) {
      pivot(matrix, i, index_array);
      for (j = i + 1; j < length; ++j) {
        matrixL->matrix[sizeL] = GET(matrix,j,i)/GET(matrix,i,i);
        SET(matrix,j,i,ZEROF);
        for (k = i + 1; k < length; ++k)
          matrix->matrix[(j*length) + k] -= matrixL->matrix[sizeL] * GET(matrix,i,k);
        sizeL++;
      }
    }
}
