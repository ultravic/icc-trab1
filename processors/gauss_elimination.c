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
t_matrix* gaussElimination(t_matrix *matrix)
{
    int j, i, k;
    int line_change;
    double column_subtract;
    double largest_column_n;
    t_matrix *matrixL;

    int sizeL = matrix->lenght - 1;
    i = sizeL - 1;
    while (i--) sizeL =+ i;

    matrixL->lenght = sizeL;
    matrixL->matrix = (double *)malloc(sizeof(double)*sizeL); //Verificar tamanho

    for (i = 0; i < (matrix->lenght - 1); ++i) {
        largest_column_n = matrix->matrix[(i*matrix->lenght) + i];
        for (j = i; j < matrix->lenght; ++j) {
            if (matrix->matrix[(j*matrix->lenght) + i] > largest_column_n) {
                largest_column_n = matrix->matrix[(j*matrix->lenght) + i];
                line_change = j;
            }
        }
        changeLines(matrix, i, line_change);
        for (j = i + 1; j < matrix->lenght; ++j) {
          matrixL->matrix[j - 1] = matrix->matrix[(j*matrix->lenght) + i]/matrix->matrix[(i*matrix->lenght) + i];
          for (k = i + 1; k < matrix->lenght; ++k)
            matrix->matrix[(j*matrix->lenght) + k] -= matrixL->matrix[j - 1] * matrix->matrix[(i*matrix->lenght) + k];
        }
    }
}
