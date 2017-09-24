/**
 * @file       partial_pivoting.h
 * @author     Pedro Luiz de Souza Moreira  GRR20163064
 * @author     Victor Picussa   GRR20163068
 * @date       24 Sep 2017
 * @brief      Esse arquivo contém os cabeçalhos das funções usadas no
 *             pivotamento parcial, que se utiliza de um vetor de troca de
 *             indices
 */

#include "datatypes.h"
#ifndef __PARTIAL_PIVOTING__
#define __PARTIAL_PIVOTING__

void initIndexArray(int *index_array, int length);

void pivot(t_matrix *M, int pos, int *index_array);

#endif