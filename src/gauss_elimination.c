/**
 * @file       gauss_elimination.c
 * @author     Pedro Luiz de Souza Moreira  GRR20163064
 * @author     Victor Picussa   GRR20163068
 * @date       24 Sep 2017
 * @brief      Esse arquivo contém a definição da função usada para a
 *             temporização do programa
 */

#include "../lib/datatypes.h"
#include "../lib/double_operations.h"
#include "../lib/gauss_elimination.h"
#include "../lib/partial_pivoting.h"
#include "../lib/io.h"
#include <stdio.h>
#include <stdlib.h>


/**
 * @brief      Inicializa uma matriz triangular
 *
 * @param      matrixL  A matriz
 * @param[in]  length   O tamanho da matriz
 */
void initMatrixL(t_matrix *matrixL, int length)
{
  matrixL->length = SEQUENTIAL_SUM(length-1);
  matrixL->matrix = ALLOC(double, matrixL->length);
}

/**
 * @brief      Funçao que efetua a eliminação gaussiana em uma matriz
 *
 * @param      A            Matriz original
 * @param      L            Matriz de multiplicadores (triangular inferior)
 * @param      U            Matriz escalonada (triangular superior)
 * @param      index_array  Vetor de troca de linhas
 *
 */
void gaussElimination(t_matrix *A, t_matrix *L, t_matrix *U, int *index_array, int length)
{
    int j, i, k, m, sizeL = 0;

    for (i = 0; i < (length - 1); ++i) {
      pivot(A, i, index_array);

      for (j = i + 1; j < length; ++j) {
        L->matrix[sizeL] = GET(A, index_array[j], i) / GET(A, index_array[i], i);
        SET(U, index_array[j], i, TRUE_ZERO);

        for (k = i + 1; k < length; ++k)
          SET(U,index_array[j], k, (GET(A,index_array[j],k) - (L->matrix[sizeL] * GET(A, index_array[i], k))) );

        sizeL++;
      }
    }
}
