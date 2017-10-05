/**
 * @file       matrix_solver.h
 * @author     Pedro Luiz de Souza Moreira  GRR20163064
 * @author     Victor Picussa   GRR20163068
 * @date       24 Sep 2017
 * @brief      Esse arquivo contém os cabeçalhos das funções:
 *             backwardSubstitution e forwardSubstituition
 */

#include "datatypes.h"
#ifndef __MATRIX_SOLVER__
#define __MATRIX_SOLVER__

void backwardSubstitution(double **A, double **B, double **X, int *line_map, int length);

void forwardSubstitution(double **A, double **B, double **X, int *line_map, int length);

#endif
