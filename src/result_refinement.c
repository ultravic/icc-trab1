/**
 * @file       result_refinement.c
 * @author     Pedro Luiz de Souza Moreira  GRR20163064
 * @author     Victor Picussa   GRR20163068
 * @date       24 Sep 2017
 * @brief      Esse arquivo contém as definições das funções usadas para realiza
 *             o refinamento do resultado da inversão
 */

#include "../lib/io.h"
#include "../lib/datatypes.h"
#include "../lib/double_operations.h"
#include "../lib/result_refinement.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>


/**
 * @brief      Efetua o produto interno de uma linha de uma matriz por uma
 *             coluna de outra matriz
 *
 * @param      A       Matriz A
 * @param      B       Matriz B
 * @param[in]  line    A linha da matriz A
 * @param[in]  column  A coluna da matriz B
 * @param[in]  length  The length
 * @param      line_map  The index array
 *
 * @return     O resultado da operação
 */
double lineTimesColumn(double **A, double **B, int line, int column, int length)
{
  int i, j;
  double temporary = TRUE_ZERO;

  for (i = 0; i < length; i+=4) {
    temporary += GET(A, length, line, i) * GET(B, length, i, column);
    temporary += GET(A, length, line, i+1) * GET(B, length, i+1, column);
    temporary += GET(A, length, line, i+2) * GET(B, length, i+2, column);
    temporary += GET(A, length, line, i+3) * GET(B, length, i+3, column);
  }

  if (i > length)
    for (j = i - 4; j < length; ++j)
      temporary += GET(A, length, line, i) * GET(B, length, i, column);

  return temporary;
}



/**
 * @brief      Efetua a soma de duas matrizes
 *
 * @param      X     Matriz
 * @param      XW    Matriz
 */
void sumMatrix(double **A, double **B, int length)
{
  int i, j;
  double aux;

  for (i = 0; i < length; ++i)
  {
    for (j = 0; j < length; ++j) {
      aux = GET(B,length, i, j) + GET(A,length, i, j);
      SET(B,length, i, j, aux);
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
void residueCalc(double **A, double **X, double **I, double **R, int length)
{
  double aux;
  int i, j;

  for (i = 0; i < length; ++i) {
    for (j = 0; j < length; ++j) {
      aux = GET(I, length, i, j) - lineTimesColumn(A, X, i, j, length);
      SET(R, length, i, j, aux);
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
double normCalc(double **R, int length)
{
  int i;
  int size = SQ(length);
  double norm;

  norm = TRUE_ZERO;
  for (i = 0; i < size; ++i)
    norm += SQ((*R)[i]);

  return sqrt(norm);
}
