/**
 * @file       time_measurement.c
 * @author     Pedro Luiz de Souza Moreira  GRR20163064
 * @author     Victor Picussa   GRRVP
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
t_matrix *backwardSubstitution(t_matrix *U, t_matrix *B, int *index_array) {
  int length = U->length;
  int last = length - 1;

  // Inicializa e aloca memória para a matriz resultante
  t_matrix *X;
  INIT_MATRIX(X);
  X->length = length;
  X->matrix = ALLOC(double, SQ(length));

  // contadores
  int i, j, k;
  int index;

  // define primeiro valor a ser usado
  double aux = GET(B, last, 1) / GET(U, last, last);

  t_kahan *kahan;
  kahan = ALLOC(t_kahan, 1);

  SET(X, last, 1, aux);

  for (k = 0; k < length; ++k) {
    INIT_KAHAN(kahan);
    for (i = last; i > 0; --i) {

      index = index_array[i];
      kahan->sum = GET(B, index, k);

      for (j = (i + 1); j < length; ++j) {
        KAHAN_SUM(kahan, (kahan->sum - (GET(U, index, j) * GET(X, j, k))));
        aux = GET(U, index, i);
        if (IS_ZERO(aux))
          die(ERROR_ZERO_DIVISION);
        SET(X, j, k, (kahan->sum / aux));
      }
    }
  }
  free(kahan);
  return X;
}
