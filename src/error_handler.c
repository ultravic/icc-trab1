/**
 * @file       error_handler.c
 * @author     Pedro Luiz de Souza Moreira  GRR20163064
 * @author     Victor Picussa   GRRVP
 * @date       24 Sep 2017
 * @brief      Esse arquivo contém a definição da função usada para abortar a execução
 */

#include "../lib/error_handler.h"
#include <stdio.h>
#include <stdlib.h>

/**
 * @brief      Exibe uma mensagem de erro, libera a memória e aborta a execução
 *
 * @param      reason  Mensagem a ser exibida
 */
void die(char const reason[]) {
  fprintf(stderr, "%s", reason);
  exit(EXIT_FAILURE);
}
