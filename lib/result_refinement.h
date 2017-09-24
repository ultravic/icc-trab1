/**
 * @file       result_refinement.h
 * @author     Pedro Luiz de Souza Moreira  GRR20163064
 * @author     Victor Picussa   GRRVP
 * @date       24 Sep 2017
 * @brief      Esse arquivo contém os cabeçalhos das funções usadas para o
 *             refinamento da matriz resultante
 */

#include "datatypes.h"
#ifndef __RESULT_REFINAMENT__
#define __RESULT_REFINAMENT__

void createIdentity(t_matrix *I, int length);

double calculateLC(t_matrix *U, t_matrix *X, int line, int column);

t_matrix* resultRefinement(t_matrix *U, t_matrix *X, t_matrix *I);

#endif
