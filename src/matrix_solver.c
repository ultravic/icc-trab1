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
#include "../lib/io.h"
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
void forwardSubstitution(double **L, double **Y, double **B, int *line_map, int length)
{
  // contadores
  int i, j, c;

  // define primeiro valor a ser usado
  double aux;

  double temp = 0;
  for (c = 0; c < length; ++c) {
    aux = GET(B, length, line_map[0], c) / GET(L, length, 0, 0);
    SET(Y, length, 0, c, aux);
    for (i = 1; i < length; ++i) {
      temp = GET(B, length, line_map[i], c);
      for (j = 0; j < i; j++) {
        temp = temp - (GET(L, length, i, j) * GET(Y, length, j, c));
      }
      temp = temp / GET(L, length, i, j);
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
void backwardSubstitution(double **U, double **X, double **Y, int *line_map, int length)
{
  int last = length - 1;

  // contadores
  int i, j, c;

  // define primeiro valor a ser usado
  double aux;

  double temp = 0;
  for (c = 0; c < length; ++c) {
    aux = GET(Y, length, last, c) / GET(U, length, line_map[last], last);
    SET_TRANSP(X, length, last, c, aux);
    for (i = last-1; i >= 0; --i) {
      temp = GET(Y, length, i, c);
      for (j = last; j > i; --j) {
        temp = temp - (GET(U, length, line_map[i], j) * GET_TRANSP(X, length, j, c));
      }
      temp = temp / GET(U, length, line_map[i], j);
      SET_TRANSP(X, length, i, c, temp);
    }
  }
}
