/**
 * @file       io.h
 * @author     Pedro Luiz de Souza Moreira  GRR20163064
 * @author     Victor Picussa   GRR20163068
 * @date       24 Sep 2017
 * @brief      Esse arquivo contém os cabeçalhos das funções usadas para tratar
 *             entrada e saída(impressão de matrizes) de dados
 */

#include "datatypes.h"
#include "stdio.h"
#ifndef __IO__
#define __IO__

int readMatrix(t_matrix * M, int *length, char *file_path);

int parseParameters(int argc, char const *argv[], param *P);

void printMatrix(t_matrix *matrix, int *index_array, FILE *file);

void printMatrixL(t_matrix *matrix, FILE *file);

void printNormal(t_matrix *matrix, FILE *file);

void printIndexes(t_matrix *m, int *index_array, FILE *file);

#endif
