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
 * @brief      Funçao que efetua a eliminação gaussiana em uma matriz
 *
 * @param      A         Matriz original
 * @param      L         Matriz de multiplicadores (triangular inferior)
 * @param      U         Matriz escalonada (triangular superior)
 * @param      line_map  vetor de mapeamento de linhas
 * @param[in]  length    Largura da matriz
 */
void gaussElimination(double **A, double **L, double **U, int *line_map, int length)
{
  int j, i, k, sizeL = 0;
  for (i = 0; i < (length - 1); ++i) {
  printf("a%d\n",length);
    pivot(A, i, line_map, length);

  printf("a%d\n",length);
    for (j = i + 1; j < length; ++j) {
      *L[sizeL] = GET(A, length, line_map[j], i) / GET(A, length, line_map[i], i);
      SET(U, length, line_map[j], i, TRUE_ZERO);
      printf("L %lf\n",*L[sizeL] );
      for (k = i + 1; k < length; ++k)
        SET(U, length, line_map[j], k, (GET(A, length, line_map[j],k) - (*L[sizeL] * GET(A, length, line_map[i], k))) );

      sizeL++;
    }
  }
}
