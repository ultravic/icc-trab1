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
 * @param[in]  n    Largura da matriz
 */
void gaussElimination(double **A, double **L, double **U, int *line_map, int n)
{
  int j, i, k, sizeL = 0;
  double aux, mult;

    for (i = 0; i < (n - 1); ++i) {
    partialPivoting(A, i, line_map, n);

      for (k = 0; k < n; ++k)
        SET(U,n,i,k,(GET(A,n,line_map[i],k)));

    printf("aaa\n");
    printMapped(A,line_map,n);

    for (j = i + 1; j < n; ++j) {
      (*L)[sizeL] = mult = GET(A, n, line_map[j], i) / GET(A, n, line_map[i], i);

      printf("%lf/%lf = %lf\n",GET(A, n, line_map[j], i),GET(A, n, line_map[i], i), mult);

      SET(U, n, j, i, TRUE_ZERO);

      for (k = i + 1; k < n; ++k){
        aux = GET(A, n, line_map[j],k) - (mult * GET(A, n, line_map[i], k));
        SET(U, n, j, k, aux);
      }
      sizeL++;
    }
    // Problema: o multiplicador está sendo calculado pelo valor desatualizado

  }
}

