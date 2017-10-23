/**
 * @file       time_measurement.c
 * @author     Pedro Luiz de Souza Moreira  GRR20163064
 * @author     Victor Picussa   GRR20163068
 * @date       24 Sep 2017
 * @brief      Esse arquivo contém a definição das funções usadas para resolução
 *             de sistemas triangulares
 */

#include "../lib/datatypes.h"
#include "../lib/double_operations.h"
#include "../lib/matrix_solver.h"
#include <stdio.h>
#include <stdlib.h>



/**
 * @brief      Efetua substituição Ax=B
 *
 * @param      A         Matriz triangular inferior
 * @param      X         Matriz resultante
 * @param      B         Matriz de termos independentes
 * @param      line_map  vetor de mapeamento de linhas
 * @param[in]  length    A largura das matrizes
 */
void forwardSubstitution(double **L, double **Y, double **B, int *line_map, int length) {
  int last = length - 1;

  // contadores
  int i, j, c;

  // define primeiro valor a ser usado
  double aux;

  double temp = 0;
  for (c = 0; c < length; ++c) {
    aux = GET(B, length, line_map[0], c) / GETT(L, 0, 0);
    SET(Y, length, 0, c, aux);

    for (i = 1; i < last; ++i) {
      temp = GET(B, length, line_map[i], c);
      for (j = 0; j <= i; j++) {
        temp = temp - (GETT(L, i-1, j) * GET(Y, length, j, c));
      }

      temp = temp / GETT(L, i-1, j);
      SET(Y, length, i, c, temp);
    }
  }

}

/**
 * @brief      Efetua substituição Ax=B
 *
 * @param      A         Matriz triangular superior
 * @param      X         Matriz resultante
 * @param      B         Matriz de termos independentes
 * @param[in]  length    A largura das matrizes
 */
void backwardSubstitution(double **A, double **X, double **B, int length) {
  int last = length - 1;

  // contadores
  int i, j, c;

  // define primeiro valor a ser usado
  double aux;

  double temp = 0;
  for (c = 0; c < length; ++c) {
    aux = GET(B, length, last, c) / GET(A, length, last, last);
    SET(X, length, last, c, aux);

    for (i = last - 1; i >= 0; --i) {
      temp = GET(B, length, i, c);
      for (j = last; j > i; --j) {
        temp = temp - (GET(A, length, i, j) * GET(X, length, j, c));
      }
      temp = temp / GET(A, length, i, j);
      SET(X, length, i, c, temp);
    }

  }
}
