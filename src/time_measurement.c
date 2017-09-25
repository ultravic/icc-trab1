/**
 * @file       time_measurement.c
 * @author     Pedro Luiz de Souza Moreira  GRR20163064
 * @author     Victor Picussa   GRR20163068
 * @date       24 Sep 2017
 * @brief      Esse arquivo contém a definição da função usada para a
 *             temporização do programa
 */
#include "../lib/time_measurement.h"

/**
 * @brief      Retorna o tempo atual do sistema
 *
 * @return     Tempo atual
 */
double timestamp(void){
    struct timeval tp;
    gettimeofday(&tp, NULL);
    return((double)(tp.tv_sec*1000.0 + tp.tv_usec/1000.0));
}