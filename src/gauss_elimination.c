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
void gaussElimination(t_matrix *mA, t_matrix *mB, t_matrix *mL, int *index_array)
{
    int j, i, k, sizeL = 0;
    int length = mA->length;

    for (i = 0; i < (length - 1); ++i) {
      pivot(mA, i, index_array);
      for (j = i + 1; j < length; ++j) {
        mL->matrix[sizeL] = GET(mA,j,i)/GET(mA,i,i);
        SET(mA,j,i,ZEROF);
        for (k = i + 1; k < length; ++k)
          mA->matrix[(j*length) + k] -= mL->matrix[sizeL] * GET(mA,i,k);
        sizeL++;
      }
    }

//    mB->matrix[(j*length) + k] -= mL->matrix[sizeL] * GET(mB,i,k);
}
