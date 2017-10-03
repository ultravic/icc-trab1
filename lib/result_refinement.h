/**
 * @file       result_refinement.h
 * @author     Pedro Luiz de Souza Moreira  GRR20163064
 * @author     Victor Picussa   GRR20163068
 * @date       24 Sep 2017
 * @brief      Esse arquivo contém os cabeçalhos das funções usadas para o
 *             refinamento da matriz resultante
 */

#include "datatypes.h"
#ifndef __RESULT_REFINAMENT__
#define __RESULT_REFINAMENT__

void initMatrixIdentity(t_matrix *I, int length);

double lineTimesColumn(t_matrix *A, t_matrix *B, int line, int column, int length);

void sumMatrix(t_matrix *A, t_matrix *B, int length);

void residueCalc(t_matrix *A, t_matrix *X, t_matrix *I, t_matrix *R, int length);

double normCalc(t_matrix *R, int length);

#endif
