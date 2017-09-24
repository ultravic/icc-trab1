/**
 * @file       matrix_generator.c
 * @author     Pedro Luiz de Souza Moreira  GRR20163064
 * @author     Victor Picussa   GRR20163068
 * @date       24 Sep 2017
 * @brief      Esse arquivo contém a definição da função usada para a
 *             geração de matrizes quadradas aleatórias
 */

#include "../lib/datatypes.h"
#include <stdlib.h>

/**
 * @brief      Dado uma largura, gera uma matriz quadrada aleatória
 *
 * @param[in]  n     A largura
 *
 * @return     A matriz gerada
 */
double *generateSquareRandomMatrix(int n) {
  double *mat = NULL;

  /* return NULL if memory allocation fails */
  if (!(mat = ALLOC(double, SQ(n))))
    return NULL;

  /* generate a randomly initialized matrix in row-major order */
  double *ptr = mat;
  double *end = mat + SQ(n);

  double invRandMax = 1.0 / (double)RAND_MAX;

  while (ptr != end) {
    *ptr++ = (double)rand() * invRandMax;
  }

  return mat;
}
