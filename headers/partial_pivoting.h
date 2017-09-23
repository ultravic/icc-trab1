#include "datatypes.h"
#ifndef __PARTIAL_PIVOTING__
#define __PARTIAL_PIVOTING__

/**
 * @brief      Inicializa o vetor de troca de linhas com uma enumeração de 0 a N-1
 *
 * @param      index_array  Vetor de troca de linhas
 * @param[in]  length       Numero de linhas do sistema
 */
void initIndexArray(int *index_array, int length);

/**
 * @brief      Encontra o maior valor de uma coluna da matriz, a partir de uma determinada posição e troca as posições no vetor de troca de
 *
 * @param[in]  M            Matriz a ser buscada
 * @param[in]  pos          A posição do valor a ser pivotado
 * @param      index_array  O vetor de troca de linhas
 */
void pivot(t_matrix *M, int pos, int *index_array);

#endif