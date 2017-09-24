#include <stdio.h>
#include <stdlib.h>
#include "../headers/gauss_elimination.h"
#include "../headers/partial_pivoting.h"
#include "../headers/printers.h"
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
void gaussElimination(t_matrix *mA, t_matrix *mB, t_matrix *mL, int *index_array)
{
    int j, i, k, sizeL = 0;
    int length = mA->length;

    for (i = 0; i < (length - 1); ++i) {
      printMatrix(mA, index_array);
      pivot(mA, i, index_array);
      printMatrix(mA, index_array);
      for (j = i + 1; j < length; ++j) {
        mL->matrix[sizeL] = GET(mA, index_array[j], i)/GET(mA, index_array[i], i);
        SET(mA, index_array[j], i, ZEROF);
        for (k = i + 1; k < length; ++k)
          mA->matrix[(index_array[j]*length) + k] -= mL->matrix[sizeL] * GET(mA, index_array[i], k);
        sizeL++;
      }
    }

    sizeL = 0;
    for (i = 0; i < length; ++i) {
      for (j = 0; j < length; ++j)
        mB->matrix[(index_array[i]*length) + j] -= mL->matrix[sizeL] * GET(mB, index_array[i], j);
      sizeL++;
    }
}
