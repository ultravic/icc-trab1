/**
 * @file       time_measurement.c
 * @author     Pedro Luiz de Souza Moreira  GRR20163064
 * @author     Victor Picussa   GRRVP
 * @date       24 Sep 2017
 * @brief      Esse arquivo contém a definição da função usada para a
 *             temporização do programa
 */

#include <stdlib.h>
#include <sys/time.h>
#include "../lib/time_measurement.h"

/**
 * @brief      Mede o tempoentre regiões de interesse
 *
 * @return     O tempo decorrido em segundos
 */
double timestamp(void) {
  struct timeval tp;
  gettimeofday(&tp, NULL);
  return ((double)(tp.tv_sec * 1000.0 + tp.tv_usec / 1000.0));
}
