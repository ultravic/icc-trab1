#include <stdio.h>

/*
    - Função que utiliza o método da eliminação de Gauss.
    - Recebe um vetor e seu tamanho.
*/
double* gaussElimination(double *matrixU, int size)
{
    int j, i;
    int line_change;
    double largest_column_n;
    double *matrixL;

    for (i = 0; i < size; ++i) {
        largest_column_n = matrixU[i*size][i];
        for (j = i; j < size; ++j) {
            if (matrixU[j*size][i] > largest_column_n) {
                largest_column_n = matrixU[j*size][i];
                line_change = j;
            }
        }
        for (j = i + 1; j < size; ++j) {

        }
        changeLines(matrixU, size, i, line_change);
    }
}

/*
    - Função criada para fazer a troca de linhas.
    - Recebe um vetor, seu tamanho e as duas linhas
   a serem trocadas.
*/
void changeLines(double *matrixU, int size, int fline, int sline) {

}
