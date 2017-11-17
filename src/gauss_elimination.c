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
  double aux, aux2, aux3, aux4, mult;
  memcpy(*U,*A,SQ(n)*sizeof(double));

  for (i = 0; i < n-1; ++i) {
    sizeL = 1;
    partialPivoting(U, L, i, line_map, n);
    for (j = i + 1; j < n; ++j) {
      mult = GET(U, n, line_map[j], i) / GET(U, n, line_map[i], i);
      SET(L, n, j, i, mult);

      SET(U, n, line_map[j], i, TRUE_ZERO);

      for (k = i + 1; k+4 < n; k+=4) {
        aux = GET(U, n, line_map[j], k) - (mult * GET(U, n, line_map[i], k));
        aux2 = GET(U, n, line_map[j], k+1) - (mult * GET(U, n, line_map[i], k+1));
        aux3 = GET(U, n, line_map[j], k+2) - (mult * GET(U, n, line_map[i], k+2));
        aux4 = GET(U, n, line_map[j], k+3) - (mult * GET(U, n, line_map[i], k+3));
        SETFC(U, n, line_map[j], k, aux, aux2, aux3, aux4);
      }

      for (; k < n; ++k) {
        aux = GET(U, n, line_map[j], k) - (mult * GET(U, n, line_map[i], k));
        SET(U, n, line_map[j], k, aux);
      }

      sizeL++;
    }
  }
}
