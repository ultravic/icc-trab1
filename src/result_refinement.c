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
#include "../lib/io.h"
#include "../lib/result_refinement.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>


/**
 * @brief      Efetua a soma de duas matrizes
 *
 * @param      X     Matriz
 * @param      XW    Matriz
 */
void sumMatrix(double **A, double **B, int length)
{
    int i, j;
    int alength = SIZE_OF_ALIGNED_LINE(length);
    double aux, aux2, aux3, aux4;

    for (i = 0; i < length; ++i) {
      for (j = 0; j+4 < length; j+=4) {
        aux = GET_TRANSP(B, alength, i, j) + GET_TRANSP(A, alength, i, j);
        aux2 = GET_TRANSP(B, alength, i, j+1) + GET_TRANSP(A, alength, i, j+1);
        aux3 = GET_TRANSP(B, alength, i, j+2) + GET_TRANSP(A, alength, i, j+2);
        aux4 = GET_TRANSP(B, alength, i, j+3) + GET_TRANSP(A, alength, i, j+3);
        SET_TRANSPFC(B, alength, i, j, aux, aux2, aux3, aux4);
      }

      for (; j < length; ++j) {
        aux = GET_TRANSP(B, alength, i, j) + GET_TRANSP(A, alength, i, j);
        SET_TRANSP(B, alength, i, j, aux);
      }
  }
}

/**
 * @brief      Executa o refinamento do resultado
 *
 * @param      U     Matriz triangular superior resultante da eliminação
 * gaussiana
 * @param      X     Matriz de resultados
 * @param      I     Matriz Identidade
 *
 * @return     Matriz de Residuos
 */
void residueCalc(double **A, double **X, double **I, double **R, int length) {
    double aux;
    int i, j, k;
    int alength = SIZE_OF_ALIGNED_LINE(length);
    // Calcula resíduo R = I - A*X
    for (i = 0; i < length; ++i) {
        for (j = 0; j < length; ++j) {
            aux = TRUE_ZERO;
            //A[i]*X[j]

            for (k = 0; k+4 < length; k+=4) {
                aux += GET(A, alength, i, k) *   GET(X, alength, j, k);
                aux += GET(A, alength, i, k+1) * GET(X, alength, j, k+1);
                aux += GET(A, alength, i, k+2) * GET(X, alength, j, k+2);
                aux += GET(A, alength, i, k+3) * GET(X, alength, j, k+3);
            }

            for (; k < length; ++k)
                aux += GET(A, alength, i, k) * GET(X, alength, j, k);

            // I-A*X
            aux = (i==j) ? TRUE_ZERO : (IS_ZERO(aux)? TRUE_ZERO : -aux);

            // R =  I-A*X
            SET(R, alength, i, j, aux);
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
double normCalc(double **R, int length) {
    int i;
    int size = SQ(length);
    double norm;

    norm = TRUE_ZERO;
    for (i = 0; i+4 < size; i+=4) {
        norm += SQ((*R)[i]);
        norm += SQ((*R)[i+1]);
        norm += SQ((*R)[i+2]);
        norm += SQ((*R)[i+3]);
    }

    for (; i < size; ++i)
        norm += SQ((*R)[i]);

    return sqrt(norm);
}
