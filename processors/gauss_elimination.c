#include <stdio.h>
#include <stdlib.h>
#include "../datatypes.h"

/*
    - Função criada para fazer a troca de linhas.
    - Recebe um vetor, seu tamanho e as duas linhas
   a serem trocadas.
*/
void changeLines(t_matrix *matrix, int fline, int sline)
{
  int i;
  double temporary;

  for (i = 0; i < matrix->lenght; ++i) {
    temporary = matrix->matrix[(fline*matrix->lenght) + i];
    matrix->matrix[(fline*matrix->lenght) + i] = matrix->matrix[(sline*matrix->lenght) + i];
    matrix->matrix[(sline*matrix->lenght) + i] = temporary;
  }
}

/*
    - Função que utiliza o método da eliminação de Gauss.
    - Recebe um vetor e seu tamanho.
*/
t_matrix gaussElimination(t_matrix *matrix)
{
    int j, i, k, sizeL = 0;
    int line_change;
    double column_subtract;
    double largest_column_n = 0.0f;
    t_matrix matrixL;

    i = matrix->lenght - 1;
    while (i) {
      sizeL += i;
      --i;
    }

    matrixL.lenght = sizeL;
    matrixL.matrix = (double *)malloc(sizeof(double)*sizeL); //Verificar tamanho
    sizeL = 0;

    for (i = 0; i < (matrix->lenght - 1); ++i) {
      line_change = i;
      largest_column_n = matrix->matrix[(i*matrix->lenght) + i];
      for (j = i; j < matrix->lenght; ++j) {
        if (matrix->matrix[(j*matrix->lenght) + i] > largest_column_n) {
            largest_column_n = matrix->matrix[(j*matrix->lenght) + i];
            line_change = j;
        }
      }
      changeLines(matrix, i, line_change);

      for (j = i + 1; j < matrix->lenght; ++j) {
        matrixL.matrix[sizeL] = matrix->matrix[(j*matrix->lenght) + i]/matrix->matrix[(i*matrix->lenght) + i];
        matrix->matrix[(j*matrix->lenght) + i] = 0.0f;
        for (k = i + 1; k < matrix->lenght; ++k)
          matrix->matrix[(j*matrix->lenght) + k] -= matrixL.matrix[sizeL] * matrix->matrix[(i*matrix->lenght) + k];
        sizeL++;
      }
    }

    return matrixL;
}
