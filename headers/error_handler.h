#ifndef __ERROR_HANDLER__
#define __ERROR_HANDLER__

static const char ERROR_PARAM[] = "Parametros inválidos!\n Favor usar:invmat [-i arquivo_entrada] [-o arquivo_saida] [-r N] -i k \n";
static const char ERROR_ZERO_DIVISION[] = "Divisão por Zero!\n Abortando... \n";
static const char ERROR_ZERO_PIVOT[] = "Pivô é Zero! Sistema possivelmente sem solução.\n Abortando... \n";

void die(char const reason[]);

#endif