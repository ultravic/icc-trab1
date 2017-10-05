/**
 * @file       gauss_elimination.h
 * @author     Pedro Luiz de Souza Moreira  GRR20163064
 * @author     Victor Picussa   GRR20163068
 * @date       24 Sep 2017
 * @brief      Esse arquivo contém uma macro para calcular o tamanho "real" de
 *             uma matriz triangular, o cabeçalho da função de eliminação
 *             gaussiana
 */

#include "datatypes.h"
#ifndef __GAUSS_ELIMINATION__
#define __GAUSS_ELIMINATION__

void gaussElimination(double **A, double **L, double **U, int *line_map, int length);

#endif
