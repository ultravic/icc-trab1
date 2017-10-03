/**
 * @file       result_refinement.c
 * @author     Pedro Luiz de Souza Moreira  GRR20163064
 * @author     Victor Picussa   GRR20163068
 * @date       24 Sep 2017
 * @brief      Esse arquivo contém as definições das funções usadas para realiza
 *             o refinamento do resultado da inversão
 */

#include "../lib/datatypes.h"
#include "../lib/double_operations.h"
#include "../lib/result_refinement.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/**
 * @brief      Cria uma matriz Identidade
 *
 * @param      I       Ponteiro para a Matriz
 * @param[in]  length  a largura da matriz
 */
void initMatrixIdentity(t_matrix *I, int length) {
  int i, j;

  I->matrix = ALLOC(double, SQ(length));

  for (i = 0; i < length; ++i)
    for (j = i + 1; j < length; ++j)
      I->matrix[i * length + j] = TRUE_ZERO;

  for (i = 0; i < length; ++i)
    I->matrix[i * length + i] = TRUE_ONE;
}


/**
 * @brief      Efetua o produto interno de uma linha de uma matriz por uma
 *             coluna de outra matriz
 *
 * @param      A       Matriz A
 * @param      B       Matriz B
 * @param[in]  line    A linha da matriz A
 * @param[in]  column  A coluna da matriz B
 * @param[in]  length  The length
 * @param      index_array  The index array
 *
 * @return     O resultado da operação
 */
double lineTimesColumn(t_matrix *A, t_matrix *B, int line, int column, int length)
{
  int i;
  double temporary = TRUE_ZERO;

  for (i = 0; i < length; ++i)
    temporary = temporary + (GET(A,line,i) * GET(B,i,column) );

  return temporary;
}



/**
 * @brief      Efetua a soma de duas matrizes
 *
 * @param      X     Matriz
 * @param      XW    Matriz
 */
void sumMatrix(t_matrix *A, t_matrix *B, int length) 
{
  int i, j;
  double aux;

  for (i = 0; i < length; ++i)
  {

    for (j = 0; j < length; ++j) {
      aux = GET(B, i, j) + GET(A, i, j);
      SET(B, i, j, aux);
    }

  }
}

/**
 * @brief      Executa o refinamento do resultado
 *
 * @param      U     Matriz triangular superior resultante da eliminação gaussiana
 * @param      X     Matriz de resultados
 * @param      I     Matriz Identidade
 *
 * @return     Matriz de Residuos
 */
void residueCalc(t_matrix *A, t_matrix *X, t_matrix *I, t_matrix *R, int length)
{
  double aux;
  int i, j;

  memcpy(R, I, sizeof(double)*SQ(length));

  for (i = 0; i < length; ++i) {

    for (j = 0; j < length; ++j) {
      aux = (GET(R, i, j) - lineTimesColumn(A, X, i, j));
      SET(R, i, j, aux);
    }

  }
}

/**
 * @brief      Calcula a norma L2 da matriz de residuos
 *
 * @param      R     Matriz de residuos
 *
 * @return     A norma
 */
double normCalc(t_matrix *R, int length)
{
  int i;
  int size = SQ(length);
  double norm;

  for (i = 0; i < size; ++i)
    norm += SQ(R->matrix[i]);

  return sqrt(norm);
}
