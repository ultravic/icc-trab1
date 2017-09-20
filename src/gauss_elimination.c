#include <stdio.h>
#include <stdlib.h>
#include "../headers/gauss_elimination.h"
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

  for (i = 0; i < matrix->length; ++i) {
    temporary = matrix->matrix[(fline*matrix->length) + i];
    matrix->matrix[(fline*matrix->length) + i] = matrix->matrix[(sline*matrix->length) + i];
    matrix->matrix[(sline*matrix->length) + i] = temporary;
  }
}

/*
    - Função que utiliza o método da eliminação de Gauss.
    - Recebe um vetor e seu tamanho.
*/
t_matrix * gaussElimination(t_matrix *matrix)
{
    int j, i, k, sizeL = 0;
    int line_change;
    // double column_subtract;
    double largest_column_n = 0.0f;
    t_matrix *matrixL;
    INIT_MATRIX(matrixL);

    i = matrix->length - 1;
    while (i) {
      sizeL += i;
      --i;
    }

    matrixL->length = sizeL;
    matrixL->matrix = ALLOC(double,sizeL); //Verificar tamanho
    sizeL = 0;

    for (i = 0; i < (matrix->length - 1); ++i) {
      line_change = i;
      largest_column_n = GET(matrix,i,i);
      for (j = i; j < matrix->length; ++j) {
        if (GET(matrix,j,i) > largest_column_n) {
            largest_column_n = GET(matrix,j,i);
            line_change = j;
        }
      }
      changeLines(matrix, i, line_change);

      for (j = i + 1; j < matrix->length; ++j) {
        matrixL->matrix[sizeL] = GET(matrix,j,i)/GET(matrix,i,i);
        SET(matrix,j,i,0.0f);
        for (k = i + 1; k < matrix->length; ++k)
          matrix->matrix[(j*matrix->length) + k] -= matrixL->matrix[sizeL] * GET(matrix,i,k);
        sizeL++;
      }
    }

    return matrixL;
}
