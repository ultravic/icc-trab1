/**
 * @file       matrix_solver.h
 * @author     Pedro Luiz de Souza Moreira  GRR20163064
 * @author     Victor Picussa   GRR20163068
 * @date       24 Sep 2017
 * @brief      Esse arquivo contém os cabeçalhos das funções:
 *             backwardSubstitution
 */

#include "datatypes.h"
#ifndef __MATRIX_SOLVER__
#define __MATRIX_SOLVER__

void backwardSubstitution(t_matrix *A, t_matrix *B, t_matrix *X, int * index_array);

void forwardSubstitution(t_matrix *A, t_matrix *B, t_matrix *X, int * index_array);

#endif
