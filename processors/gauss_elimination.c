#include <stdio.h>

/*
    - Função que utiliza o método da eliminação de Gauss.
    - Recebe um vetor e seu tamanho.
*/
t_matriz* gaussElimination(t_matrix *matrix, int size)
{
    int j, i, k;
    int line_change;
    double column_subtract;
    double largest_column_n;
    t_matriz *matrixL;

    int sizeL = size - 1;
    int i = sizeL - 1;
    while (i--) sizeL =+ i;

    matrixL.matrix = sizeL;
    matrixL.matrix = malloc(sizeof(double)*sizeL); //Verificar tamanho

    for (i = 0; i < (size - 1); ++i) {
        largest_column_n = matrix.matrix[(i*size) + i];
        for (j = i; j < size; ++j) {
            if (matrix.matrix[(j*size) + i] > largest_column_n) {
                largest_column_n = matrix.matrix[(j*size) + i];
                line_change = j;
            }
        }
        changeLines(matrix, size, i, line_change);
        for (j = i + 1; j < size; ++j) {
          matrixL[j - 1] = matrix.matrix[(j*size) + i]/matrix.matrix[(i*size) + i];
          for (k = i + 1; k < size; ++k)
            matrix.matrix[(j*size) + k] -= matrixL[j - 1] * matrix.matrix[(i*size) + k];
        }
    }
}

/*
    - Função criada para fazer a troca de linhas.
    - Recebe um vetor, seu tamanho e as duas linhas
   a serem trocadas.
*/
void changeLines(double *matrix, int size, int fline, int sline)
{
  int i;
  double temporary;

  for (i = 0; i < size; ++i) {
    temporary = matrix.matrix[(fline*size) + i];
    matrix.matrix[(fline*size) + i] = matrix.matrix[(sline*size) + i];
    matrix.matrix[(sline*size) + i] = temporary;
  }
}
