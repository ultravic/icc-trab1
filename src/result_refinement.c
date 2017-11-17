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
    int i1, i2, i3;
    double aux, aux2, aux3, aux4;

    for (i = 0; i+4 < length; i+=4) {
      i1 = i+1; i2 = i+2; i3 = i+3;
      for (j = 0; j+4 < length; j+=4) {
        aux = GET_TRANSP(B, length, i, j) + GET_TRANSP(A, length, i, j);
        aux2 = GET_TRANSP(B, length, i, j+1) + GET_TRANSP(A, length, i, j+1);
        aux3 = GET_TRANSP(B, length, i, j+2) + GET_TRANSP(A, length, i, j+2);
        aux4 = GET_TRANSP(B, length, i, j+3) + GET_TRANSP(A, length, i, j+3);
        SET_TRANSPFC(B, length, i, j, aux, aux2, aux3, aux4);

        aux = GET_TRANSP(B, length, i1, j) + GET_TRANSP(A, length, i1, j);
        aux2 = GET_TRANSP(B, length, i1, j+1) + GET_TRANSP(A, length, i1, j+1);
        aux3 = GET_TRANSP(B, length, i1, j+2) + GET_TRANSP(A, length, i1, j+2);
        aux4 = GET_TRANSP(B, length, i1, j+3) + GET_TRANSP(A, length, i1, j+3);
        SET_TRANSPFC(B, length, i1, j, aux, aux2, aux3, aux4);

        aux = GET_TRANSP(B, length, i2, j) + GET_TRANSP(A, length, i2, j);
        aux2 = GET_TRANSP(B, length, i2, j+1) + GET_TRANSP(A, length, i2, j+1);
        aux3 = GET_TRANSP(B, length, i2, j+2) + GET_TRANSP(A, length, i2, j+2);
        aux4 = GET_TRANSP(B, length, i2, j+3) + GET_TRANSP(A, length, i2, j+3);
        SET_TRANSPFC(B, length, i2, j, aux, aux2, aux3, aux4);

        aux = GET_TRANSP(B, length, i3, j) + GET_TRANSP(A, length, i3, j);
        aux2 = GET_TRANSP(B, length, i3, j+1) + GET_TRANSP(A, length, i3, j+1);
        aux3 = GET_TRANSP(B, length, i3, j+2) + GET_TRANSP(A, length, i3, j+2);
        aux4 = GET_TRANSP(B, length, i3, j+3) + GET_TRANSP(A, length, i3, j+3);
        SET_TRANSPFC(B, length, i3, j, aux, aux2, aux3, aux4);
      }

      for (; j < length; ++j) {
        aux = GET_TRANSP(B, length, i, j) + GET_TRANSP(A, length, i, j);
        aux2 = GET_TRANSP(B, length, i1, j) + GET_TRANSP(A, length, i1, j);
        aux3 = GET_TRANSP(B, length, i2, j) + GET_TRANSP(A, length, i2, j);
        aux4 = GET_TRANSP(B, length, i3, j) + GET_TRANSP(A, length, i3, j);
        SET_TRANSPFL(B, length, i, j, aux, aux2, aux3, aux4);
      }
  }

  for (; i < length; ++i) {
    for (j = 0; j+4 < length; j+=4) {
      aux = GET_TRANSP(B, length, i, j) + GET_TRANSP(A, length, i, j);
      aux2 = GET_TRANSP(B, length, i, j+1) + GET_TRANSP(A, length, i, j+1);
      aux3 = GET_TRANSP(B, length, i, j+2) + GET_TRANSP(A, length, i, j+2);
      aux4 = GET_TRANSP(B, length, i, j+3) + GET_TRANSP(A, length, i, j+3);
      SET_TRANSPFC(B, length, i, j, aux, aux2, aux3, aux4);
    }

    for (; j < length; ++j) {
      aux = GET_TRANSP(B, length, i, j) + GET_TRANSP(A, length, i, j);
      SET_TRANSP(B, length, i, j, aux);
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
void residueCalc(double **A, double **X, double **R, int length) {
    double aux;
    int i, j, k;

    // Calcula resíduo R = I - A*X
    for (i = 0; i < length; ++i) {
        for (j = 0; j < length; ++j) {
            aux = TRUE_ZERO;
            //A[i]*X[j]
            for (k = 0; k+4 < length; k+=4) {
                aux += GET(A, length, i, k) * GET(X, length, j, k);
                aux += GET(A, length, i, k+1) * GET(X, length, j, k+1);
                aux += GET(A, length, i, k+2) * GET(X, length, j, k+2);
                aux += GET(A, length, i, k+3) * GET(X, length, j, k+3);
            }

            for (; k < length; ++k)
                aux += GET(A, length, i, k) * GET(X, length, j, k);

            // I-A*X
            aux = (i==j) ? TRUE_ZERO : (IS_ZERO(aux)? TRUE_ZERO : -aux);

            // R =  I-A*X
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
