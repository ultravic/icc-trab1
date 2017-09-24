/**
 * @file       matrix_solver.h
 * @author     Pedro Luiz de Souza Moreira  GRR20163064
 * @author     Victor Picussa   GRRVP
 * @date       24 Sep 2017
 * @brief      Esse arquivo contém os cabeçalhos das funções:
 *             backwardSubstitution
 */

#include "datatypes.h"
#ifndef __MATRIX_SOLVER__
#define __MATRIX_SOLVER__

t_matrix* backwardSubstitution(t_matrix *U, t_matrix *B, int * index_array);

#endif