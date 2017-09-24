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

/**
 * @brief      Retorna a soma dos numeros de 1 a N
 *
 * @param      n     o numero final
 */
#define SEQUENTIAL_SUM(n) (int)(((1 + (n)) * (n)) / 2)

t_matrix * gaussElimination(t_matrix* matrix, int *index_change);

#endif
