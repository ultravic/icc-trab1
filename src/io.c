/**
 * @file       io.c
 * @author     Pedro Luiz de Souza Moreira  GRR20163064
 * @author     Victor Picussa   GRR20163068
 * @date       24 Sep 2017
 * @brief      Esse arquivo contém as definições das funções utilizada na
 *             entrada e saída de dados temporização do programa
 */

#include "../lib/io.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * @brief      Le uma matriz n*n
 *
 * @param      M          Matriz onde serão guardados os valores lidos
 * @param      file_path  Arquivo a ser lido, ou "stdin"
 *
 * @return     0 Caso tenha sucesso
 */
int readMatrix(t_matrix *M, int *length, char *file_path) {
  FILE *file;

  // contadores
  int i = 0;
  int c = 0;
  int size;

  if (strcmp(file_path, "stdin") == 0)
    file = stdin;
  else
    file = fopen(file_path, "r");

  if (file) {
    if (fscanf(file, "%d\n", length) == ERROR)
      return ERROR;

    M->matrix = ALLOC(double, SQ((*length)));
    size = SQ((*length));

    for (i = 0; i < size; ++i)
      c = fscanf(file, "%lf ", &M->matrix[i]);

    fclose(file);

    if (c != 1)
      return ERROR;

    return SUCCESS;
  };

  return ERROR;
}

/**
 * @brief      Função que preenche uma estrutura de parametros, pelos argumentos da execução do programa
 *
 * @param[in]  argc  Numero de argumentos
 * @param      argv  Vetor de argumentos
 * @param      P     Estrutura pra salvar os parametros
 *
 * @return     0 caso obtenha sucesso, 1 caso falhe
 */
int parseParameters(int argc, char const *argv[], param *P) {
  // contador
  int i;
  bool e = false;
  // Verifica se parametros tem chance de estarem no padrão
  if (!((argc >= 2) && (argc % 2 != 0)))
    return ERROR;
  else {
    // Trata parametros
    for (i = 1; i < argc && argv[i][0] == '-'; i++) {
      switch (argv[i][1]) {
      case 'e': // Input file?
        i++;
        P->in_file = (char *)argv[i];
        e = true;
        break;
      case 'o': // output file?
        i++;
        P->to_file = true;
        P->out_file = (char *)argv[i];
        break;
      case 'r': // random?
        i++;
        if(!e){
          P->random = true;
          P->N = atoi(argv[i]);
        }
        break;
      case 'i': // iterações
        i++;
        P->K = atoi(argv[i]);
        if(P->K < 0)
          die(ERROR_PARAM_NEGATIVE_K);
        break;
      default:
        return ERROR;
      }
    }

  }
  return SUCCESS;
}

/**
 * @brief      Imprime a matriz no formato especificado
 *
 * @param      M     Matriz a ser impressa
 */
void printMatrix(t_matrix *matrix, int *index_array, FILE *file)
{
  int i, j;
  int length = matrix->length;

  fprintf(file,"%d\n",length);

  for (i = 0; i < length; ++i) {
    for (j = 0; j < length; j++)
      fprintf(file,"%.17g " , GET(matrix, index_array[i], j));
    fprintf(file,"\n");
  }
}

 /**
  * @brief      Imprime uma matriz sequncialmente
  *
  * @param      matrix  The matrix
  */
void printMatrixL(t_matrix *matrix, FILE *file)
{
  int i;

  fprintf(file,"%d\n", matrix->length);

  for (i = 0; i < matrix->length; ++i)
    fprintf(file,"%.17g\n", GET(matrix, 0, i));
}


void printNormal(t_matrix *matrix, FILE *file)
{
  int i, j;
  int length = matrix->length;

  fprintf(file,"%d\n",length);

  for (i = 0; i < length; ++i) {
    for (j = 0; j < length; j++)
      fprintf(file,"%.17g " , GET(matrix, i, j));
    fprintf(file,"\n");
  }
}

void printIndexes(t_matrix *m, int *index_array, FILE *file)
{
  int i;

  fprintf(file,"Indexes: \n");

  for (i = 0; i < m->length; ++i)
    fprintf(file,"%d, ", index_array[i]);

  fprintf(file,"\n");
}

