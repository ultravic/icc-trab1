/**
 * @file       time_measurement.c
 * @author     Pedro Luiz de Souza Moreira  GRR20163064
 * @author     Victor Picussa   GRRVP
 * @date       24 Sep 2017
 * @brief      Esse arquivo contém a definição das funções utilizadas no
 *             pivotamento parcial
 */

#include "../lib/datatypes.h"
#include "../lib/double_operations.h"
#include "../lib/partial_pivoting.h"
#include <stdio.h>
#include <stdlib.h>

/**
 * @brief      Inicializa o vetor de troca de linhas com uma enumeração de 0 a N-1
 *
 * @param      index_array  Vetor de troca de linhas
 * @param[in]  length       Numero de linhas do sistema
 */
void initIndexArray(int *index_array, int length) {
  int i;
  for (i = 0; i < length; ++i) {
    index_array[i] = i;
  }
}

/**
 * @brief      Encontra o maior valor de uma coluna da matriz, a partir de uma determinada posição e troca as posições no vetor de troca de
 *
 * @param[in]  M            Matriz a ser buscada
 * @param[in]  pos          A posição do valor a ser pivotado
 * @param      index_array  O vetor de troca de linhas
 */
void pivot(t_matrix *M, int pos, int *index_array) {
  int i, length;
  int max_line = pos;

  double max_num = GET(M, pos, pos);
  double aux;
  length = M->length;

  for (i = pos + 1; i < length; ++i) {
    if ((aux = GET(M, pos, i)) > max_num) {
      max_num = aux;
      max_line = i;
    }
  }
  if (IS_ZERO(ABS(max_num)))
    die(ERROR_ZERO_PIVOT);

  index_array[pos] = max_line;
  index_array[max_line] = pos;
}
