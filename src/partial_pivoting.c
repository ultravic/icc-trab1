/**
 * @file       time_measurement.c
 * @author     Pedro Luiz de Souza Moreira  GRR20163064
 * @author     Victor Picussa   GRR20163068
 * @date       24 Sep 2017
 * @brief      Esse arquivo contém a definição das funções utilizadas no
 *             pivotamento parcial
 */

#include "../lib/datatypes.h"
#include "../lib/double_operations.h"
#include "../lib/partial_pivoting.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
/**
 * @brief      Encontra o maior valor de uma coluna da matriz, a partir de uma
 *             determinada posição e troca as posições no vetor de troca de
 *
 * @param[in]  M            Matriz a ser buscada
 * @param[in]  pos          A posição do valor a ser pivotado
 * @param      line_map  O vetor de mapeamento de linhas
 */
void partialPivoting(double **M, double **L, int pos, int *line_map, int length){
    int i;
    int max_line = pos;
    double max_num = fabs(GET(M, length, line_map[pos], pos));
    double aux;

    for (i = pos+1; i < length; ++i) {
        aux = GET(M, length, line_map[i], pos);
        if(fabs(aux) > max_num) {
            max_num = fabs(aux);
            max_line = i;
        }
    }

    if(IS_ZERO(max_num))
        die(ERROR_ZERO_PIVOT);
    aux = line_map[pos];
    line_map[pos] = line_map[max_line];
    line_map[max_line] = aux;

    for (i = 0; i < pos; i++) {
      aux = GET(L, length, pos, i);
      SET(L, length, pos, i, (GET(L, length, max_line, i)));
      SET(L, length, max_line, i, aux);
    }
}
