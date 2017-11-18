/**
 * @file       matrix_generator.c
 * @author     Pedro Luiz de Souza Moreira  GRR20163064
 * @author     Victor Picussa   GRR20163068
 * @date       24 Sep 2017
 * @brief      Esse arquivo contém a definição da função usada para a
 *             geração de matrizes quadradas aleatórias
 */

#include "../lib/datatypes.h"
#include "../lib/double_operations.h"
#include <stdlib.h>
#include <stdio.h>

/**
 * @brief      Dado uma largura, gera uma matriz quadrada aleatória
 *
 * @param[in]  length     A largura
 *
 * @return     A matriz gerada
 */
double *generateRandomSquareMatrix(int length) {
  double *mat = NULL;

  /* return NULL if memory allocation fails */
  if (!(mat = ALLOC(double, SQ(length))))
    return NULL;

  /* generate a randomly initialized matrix in row-major order */
  double *ptr = mat;
  double *end = mat + SQ(length);

  double invRandMax = 1.0 / (double)RAND_MAX;

  while (ptr != end) {
    *ptr++ = (double)rand() * invRandMax;
  }

  return mat;
}

/**
 * @brief      Gera uma matriz Identidade
 *
 * @param      I       Ponteiro para a Matriz
 * @param[in]  length  a largura da matriz
 */
double* generateIdentityMatrix(int length){

  int i, j;

  double *I = ALLOC(double, SQ(length));

  for (i = 0; i < length; ++i)
    for (j = i + 1; j < length; ++j)
      I[i * length + j] = TRUE_ZERO;

  for (i = 0; i < length; ++i)
    I[i * length + i] = TRUE_ONE;
  return I;
}

/**
 * @brief      Inicializa o vetor de mapeamento de linhas com uma enumeração de
 *             0 a N-1
 *
 * @param[in]  length  Numero de linhas do sistema
 *
 * @return     O vetor de mapeamento de linhas
 */
int* generateLineMap(int length) {
  int i;
  int *line_map = ALLOC(int,length);

  for (i = 0; i < length; ++i) {
    line_map[i] = i;
  }
  return line_map;
}
