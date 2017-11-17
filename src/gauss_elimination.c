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
#include <string.h>


/**
 * @brief      Funçao que efetua a eliminação gaussiana em uma matriz
 *
 * @param      A         Matriz original
 * @param      L         Matriz de multiplicadores (triangular inferior)
 * @param      U         Matriz escalonada (triangular superior)
 * @param      line_map  vetor de mapeamento de linhas
 * @param[in]  n    Largura da matriz
 */
void gaussElimination(double **A, double **L, double **U, int *line_map, int n)
{
  int j, i, k, sizeL;
  double aux, mult;
  memcpy(*U,*A,SQ(n)*sizeof(double));
  int an = SIZE_OF_ALIGNED_LINE(n);
  for (i = 0; i < n-1; ++i) {
    sizeL = 1;
    partialPivoting(U, L, i, line_map, n);
    for (j = i + 1; j < n; ++j) {
      mult = GET(U, an, line_map[j], i) / GET(U, an, line_map[i], i);
      SET(L, an, j, i, mult);

      SET(U, an, line_map[j], i, TRUE_ZERO);

      for (k = i + 1; k < n; ++k) {
        aux = GET(U, an, line_map[j], k) - (mult * GET(U, an, line_map[i], k));
        SET(U, an, line_map[j], k, aux);
      }
      sizeL++;
    }
  }
}
