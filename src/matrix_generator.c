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
  ALLOC(mat,double, SIZE_OF_ALIGNED_MATRIX(length));
  if (!(mat))
    return NULL;

  /* generate a randomly initialized matrix in row-major order */
  int size = SIZE_OF_ALIGNED_LINE(length);
  
  double invRandMax = 1.0 / (double)RAND_MAX;

  for (int i = 0; i < length; ++i)
  {
    for (int j = 0; j < length; ++j)
    {
      mat[i*size+j] = (double)rand() * invRandMax;
    }
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

  double *I = NULL;
  int alength = SIZE_OF_ALIGNED_LINE(length);

  ALLOC(I,double, SIZE_OF_ALIGNED_MATRIX(length));

  for (i = 0; i < length; ++i)
    for (j = i + 1; j < length; ++j)
      I[i * alength + j] = TRUE_ZERO;

  for (i = 0; i < length; ++i)
    I[i * alength + i] = TRUE_ONE;
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
  int *line_map = NULL; 
  ALLOC(line_map,int,length);

  for (i = 0; i < length; ++i) {
    line_map[i] = i;
  }
  return line_map;
}