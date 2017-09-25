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
 * @param      U            Matriz triangular superior
 * @param      B            Matriz de termos independentes
 * @param      index_array  Vetor de troca de linhas
 *
 * @return     A Matriz resultante
 */
void backwardSubstitution(t_matrix *U, t_matrix *B, t_matrix *X, int *index_array, char type) {
  int length = U->length;
  int last = length - 1;


  // contadores
  int i, j, c;

  // define primeiro valor a ser usado
  double aux;

  //
  // t_kahan *kahan;
  // kahan = ALLOC(t_kahan, 1);
  //
  // SET(X, last, 1, aux);
  //
  // for (k = 0; k < length; ++k) {
  //   INIT_KAHAN(kahan);
  //   for (i = last; i > 0; --i) {
  //
  //     index = index_array[i];
  //     kahan->sum = GET(B, index, k);
  //
  //     for (j = (i + 1); j < length; ++j) {
  //       KAHAN_SUM(kahan, (kahan->sum - (GET(U, index, j) * GET(X, j, k))));
  //       aux = GET(U, index, i);
  //       if (IS_ZERO(aux))
  //         die(ERROR_ZERO_DIVISION);
  //       SET(X, j, k, (kahan->sum / aux));
  //     }
  //   }
  // }
  // free(kahan);
  // return X;
  //
  double temp = 0;
  if (type == 'A') {
    for (c = 0; c < length; ++c) {
      aux = GET(B, index_array[last], c) / GET(U, index_array[last], last);
      SET(X, last, c, aux);

      for (i = last - 1; i >= 0; --i) {
        temp = GET(B, index_array[i], c);
        for (j = last; j > i; --j) {
          temp = temp - (GET(U, index_array[i], j) * GET(X, j, c));
        }
        temp = temp / GET(U, index_array[i], j);
        SET(X, i, c, temp);
      }
    }
  } else {
    for (c = 0; c < length; ++c) {
      aux = GET(B, last, c) / GET(U, index_array[last], last);
      SET(X, last, c, aux);

      for (i = last - 1; i >= 0; --i) {
        temp = GET(B, i, c);
        for (j = last; j > i; --j) {
          temp = temp - (GET(U, index_array[i], j) * GET(X, j, c));
        }
        temp = temp / GET(U, index_array[i], j);
        SET(X, i, c, temp);
      }
    }
  }
}
