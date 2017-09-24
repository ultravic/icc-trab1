/**
 * @file       error_handler.h
 * @author     Pedro Luiz de Souza Moreira  GRR20163064
 * @author     Victor Picussa   GRR20163068
 * @date       24 Sep 2017
 * @brief      Esse arquivo contém algumas constantes(mensagens de erro) e uma
 *             função para abortar a execução quando algum erro acontece
 */

#ifndef __ERROR_HANDLER__
#define __ERROR_HANDLER__

/** @brief     Erro */
#define ERROR -1

/** @brief    Sucesso */
#define SUCCESS 0

/** @brief    Erros nos Parametros */
static const char ERROR_PARAM[] = "Parametros inválidos!\n Favor usar:invmat [-i arquivo_entrada] [-o arquivo_saida] [-r N] -i k \n";

/** @brief    Erro de divisão por zero */
static const char ERROR_ZERO_DIVISION[] = "Divisão por Zero!\n Abortando... \n";

/** @brief    Erro de matriz possivelmente sem solução */
static const char ERROR_ZERO_PIVOT[] = "Pivô é Zero! Sistema possivelmente sem solução.\n Abortando... \n";

void die(char const reason[]);

#endif