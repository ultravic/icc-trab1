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

int parseParameters(int argc, char const *argv[], param *P);

int readMatrix(matrixPack *M, char *file_path);

void printMapped(double **matrix, int *line_map, int length);

void printfMapped(double **matrix, int *line_map, FILE *file, int length);

void printMatrixL(double **matrix, FILE *file, int length);

void printNormal(double **matrix, int length);

void printIndexes(double **matrix, int *line_map, FILE *file, int length);

#endif
