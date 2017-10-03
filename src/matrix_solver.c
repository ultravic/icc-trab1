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
 * @brief      Efetua retrosubstituição
 *
 * @param      A            Matriz triangular superior
 * @param      B            Matriz de termos independentes
 * @param      X            Matriz resultante
 * @param      index_array  Vetor de troca de linhas
 */
void backwardSubstitution(t_matrix *A, t_matrix *B, t_matrix *X, int *index_array) {
  int length = A->length;
  int last = length - 1;


  // contadores
  int i, j, c;

  // define primeiro valor a ser usado
  double aux;

  double temp = 0;
  for (c = 0; c < length; ++c) {
    aux = GET(B, index_array[last], c) / GET(A, index_array[last], last);
    SET(X, last, c, aux);

    for (i = last - 1; i >= 0; --i) {
      temp = GET(B, index_array[i], c);
      for (j = last; j > i; --j) {
        temp = temp - (GET(A, index_array[i], j) * GET(X, j, c));
      }
      temp = temp / GET(A, index_array[i], j);
      SET(X, i, c, temp);
    }

  }
}

/**
 * @brief      Efetua substituição
 *
 * @param      A            Matriz triangular inferior
 * @param      B            Matriz de termos independentes
 * @param      X            Matriz resultatne
 * @param      index_array  Vetor de troca de linhas
 */
void forwardSubstitution(t_matrix *A, t_matrix *B, t_matrix *X, int *index_array) {
  int length = A->length;
  int last = length - 1;

  // contadores
  int i, j, c;

  // define primeiro valor a ser usado
  double aux;

  double temp = 0;
  for (c = 0; c < length; ++c) {
    aux = GET(B, index_array[0], c) / GET(A, index_array[0], 0);
    SET(X, 0, c, aux);

    for (i = 1; i < last; ++i) {
      temp = GET(B, index_array[i], c);

      for (j = i; j >= 0; j++) {
        temp = temp - (GET(A, index_array[i], j) * GET(X, j, c));
      }

      temp = temp / GET(A, index_array[i], j);
      SET(X, i, c, temp);
    }
  }

}
