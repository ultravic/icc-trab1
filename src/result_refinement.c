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

  I->length = length;
  I->matrix = ALLOC(double, SQ(length));

  for (i = 0; i < length; ++i)
    for (j = i + 1; j < length; ++j)
      I->matrix[i * length + j] = TRUE_ZERO;

  for (i = 0; i < length; ++i)
    I->matrix[i * length + i] = 1.0;
}

/**
 * @brief      Calcula a matriz
 *
 * @param      U       { parameter_description }
 * @param      X       { parameter_description }
 * @param[in]  line    The line
 * @param[in]  column  The column
 *
 * @return     The lc.
 */
double calculateLC(t_matrix *U, t_matrix *X, int *index_array, int line, int column) {
  int i;
  double temporary = TRUE_ZERO;
  for (i = 0; i < U->length; ++i)
    temporary += U->matrix[(index_array[line]*U->length) + i] + X->matrix[i*X->length + column];
  return temporary;
}



/**
 * @brief      Efetua a soma de duas matrizes
 *
 * @param      X     Matriz
 * @param      XW    Matriz
 */
void sumMatrix(t_matrix *X, t_matrix *XW)
{
  int i, j;
  for (i = 0; i < X->length; ++i)
    for (j = 0; j < X->length; ++j)
      SET(XW, i, j, (GET(XW, i, j) + GET(X, i, j)));
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
void resultRefinement(t_matrix *U, t_matrix *X, t_matrix *I, t_matrix *B, int *index_array){

  int length = U->length;

  // inicializa estrutura auxiliar
  t_kahan *kahan;
  kahan = ALLOC(t_kahan, 1);
  INIT_KAHAN(kahan);
  double aux;

  int i, j;
  for (i = 0; i < length; ++i) {
    for (j = 0; j < length; ++j) {
      aux = (GET(B, i, j) - calculateLC(U, X, index_array, i, j));
      KAHAN_SUM(kahan, aux);
      SET(B, i, j, kahan->sum);
    }
  }
  free(kahan);
}

/**
 * @brief      Calcula a norma L2 da matriz de residuos
 *
 * @param      R     Matriz de residuos
 *
 * @return     A norma
 */
double calculateL2Norm(t_matrix *R){
  int i;
  int size = SQ(R->length);
  double norm;
  t_kahan *kahan;
  kahan = ALLOC(t_kahan, 1);
  INIT_KAHAN(kahan);

  for (i = 0; i < size; ++i)
  {
    KAHAN_SUM(kahan,R->matrix[i]);
  }
  norm = kahan->sum;
  free(kahan);
  return sqrt(norm);
}