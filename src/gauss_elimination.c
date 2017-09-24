/**
 * @file       gauss_elimination.c
 * @author     Pedro Luiz de Souza Moreira  GRR20163064
 * @author     Victor Picussa   GRRVP
 * @date       24 Sep 2017
 * @brief      Esse arquivo contém a definição da função usada para a
 *             temporização do programa
 */

#include "../lib/datatypes.h"
#include "../lib/double_operations.h"
#include "../lib/gauss_elimination.h"
#include "../lib/partial_pivoting.h"
#include <stdio.h>
#include <stdlib.h>

/**
 * @brief      Funçao que efetua a eliminação gaussiana em uma matriz
 *
 * @param      matrix        Matriz a ser escalonada
 * @param      index_change  Vetor de troca de linhas
 *
 * @return     Uma matriz triangular inferior com os multiplos utilizados na
 * eliminação
 */
t_matrix *gaussElimination(t_matrix *matrix, int *index_array) {

  int j, i, k, sizeL = 0;
  int length = matrix->length;

  // Inicialização de matriz L e Alocação de Memória
  t_matrix *matrixL;
  INIT_MATRIX(matrixL);
  matrixL->length = sizeL = SEQUENTIAL_SUM(length);
  matrixL->matrix = ALLOC(double, sizeL);

  sizeL = 0;

  for (i = 0; i < (length - 1); ++i) {
    pivot(matrix, i, index_array);
    for (j = i + 1; j < length; ++j) {
      matrixL->matrix[sizeL] = GET(matrix, j, i) / GET(matrix, i, i);
      SET(matrix, j, i, TRUE_ZERO);
      for (k = i + 1; k < length; ++k)
        GET(matrix, j, k) -= matrixL->matrix[sizeL] * GET(matrix, i, k);
      sizeL++;
    }
  }

  return matrixL;
}
