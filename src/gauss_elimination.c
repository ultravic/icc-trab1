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
  matrixL->length = SEQUENTIAL_SUM(length);
  matrixL->matrix = ALLOC(double, matrixL->length);
}

/**
 * @brief      Funçao que efetua a eliminação gaussiana em uma matriz
 *
 * @param      matrix        Matriz a ser escalonada
 * @param      index_change  Vetor de troca de linhas
 *
 * @return     Uma matriz triangular inferior com os multiplos utilizados na
 * eliminação
 */
void gaussElimination(t_matrix *mA, t_matrix *mB, t_matrix *mL, int *index_array)
{
    int j, i, k, m, sizeL = 0;
    int length = mA->length;

    for (i = 0; i < (length - 1); ++i) {
      pivot(mA, i, index_array);
      for (j = i + 1; j < length; ++j) {
        mL->matrix[sizeL] = GET(mA, index_array[j], i)/GET(mA, index_array[i], i);
        SET(mA, index_array[j], i, TRUE_ZERO);
        for (k = i + 1; k < length; ++k)
          mA->matrix[(index_array[j]*length) + k] -= mL->matrix[sizeL] * GET(mA, index_array[i], k);
        for (m = 0; m < length; ++m)
          mB->matrix[(index_array[j]*length) + m] -= mL->matrix[sizeL] * GET(mB, index_array[i], m);
        sizeL++;
      }
    }


// for (i = 0; i < (length - 1); ++i) {
//   pivot(matrix, i, index_array);
//   for (j = i + 1; j < length; ++j) {
//     matrixL->matrix[sizeL] = GET(matrix, j, i) / GET(matrix, i, i);
//     SET(matrix, j, i, TRUE_ZERO);
//     for (k = i + 1; k < length; ++k)
//       GET(matrix, j, k) -= matrixL->matrix[sizeL] * GET(matrix, i, k);
//     sizeL++;
//   }
// }

}
