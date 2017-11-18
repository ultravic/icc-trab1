/**
 * @file       result_refinement.h
 * @author     Pedro Luiz de Souza Moreira  GRR20163064
 * @author     Victor Picussa   GRR20163068
 * @date       24 Sep 2017
 * @brief      Esse arquivo contém os cabeçalhos das funções usadas para o
 *             refinamento da matriz resultante
 */

#include "datatypes.h"
#include <string.h>
#ifndef __RESULT_REFINAMENT__
#define __RESULT_REFINAMENT__

double lineTimesColumn(double **A, double **B, int line, int column, int length);

void sumMatrix(double **A, double **B, int length);

void residueCalc(double **A, double **X, double **R, int length);

double normCalc(double **R, int length);

#endif
