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
 * @brief      Le uma matriz n*n
 *
 * @param      M          Matriz onde serão guardados os valores lidos
 * @param      file_path  Arquivo a ser lido, ou "stdin"
 *
 * @return     0 Caso tenha sucesso
 */
int readMatrix(matrixPack *M, char *file_path) {
  FILE *file;

  // contadores
  int i = 0;
  int j = 0;
  int c = 0;
  int size;
  double temp;

  if (strcmp(file_path, "stdin") == 0)
    file = stdin;
  else
    file = fopen(file_path, "r");

  if (file) {
    if (fscanf(file, "%d\n", &(*M).length) == ERROR)
      return ERROR;
    size = SIZE_OF_ALIGNED_MATRIX(M->length);
    ALLOC(M->A, double, size);

    for (i = 0; i < M->length; ++i)
      for (j = 0; i < M->length; ++j){
        c = fscanf(file, "%lf ", &temp);
        SET(&(*M).A,size,i,j,temp);
      }

    fclose(file);

    if (c != 1)
      return ERROR;

    return SUCCESS;
  };

  return ERROR;
}


/**
 * @brief      Imprime a matriz no formato especificado
 *
 * @param      M     Matriz a ser impressa
 */
void printMapped(double **matrix, int *line_map, int length)
{
  int i, j;
  int alength = SIZE_OF_ALIGNED_LINE(length);
  printf("%d\n",length);
  for (i = 0; i < length; ++i) {
    for (j = 0; j < length; j++)
      printf("%1.17g\t" , GET(matrix, alength, line_map[i], j));
    printf("\n");
  }
}

/**
 * @brief      Imprime a matriz no formato especificado
 *
 * @param      M     Matriz a ser impressa
 */
void printTranspMapped(double **matrix, int *line_map, int length)
{
  int i, j;
  int alength = SIZE_OF_ALIGNED_LINE(length);
  printf("%d\n",length);
  for (i = 0; i < length; ++i) {
    for (j = 0; j < length; j++)
      printf("%1.17g\t" , GET_TRANSP(matrix, alength, line_map[i], j));
    printf("\n");
  }
}

/**
 * @brief      Imprime a matriz no formato especificado
 *
 * @param      M     Matriz a ser impressa
 */
void printfMapped(double **matrix, int *line_map, FILE *file, int length)
{
  int i, j;
  int alength = SIZE_OF_ALIGNED_LINE(length);
  fprintf(file,"%d\n",length);
  for (i = 0; i < length; ++i) {
    for (j = 0; j < length; j++)
      fprintf(file,"%1.17g\t" , GET(matrix, alength, i, j));
    fprintf(file,"\n");
  }
}

/**
 * @brief      Imprime a matriz no formato especificado
 *
 * @param      M     Matriz a ser impressa
 */
void printfTranspMapped(double **matrix, int *line_map, FILE *file, int length)
{
  int i, j;
  fprintf(file,"%d\n",length);

  int alength = SIZE_OF_ALIGNED_LINE(length);
  for (i = 0; i < length; ++i) {
    for (j = 0; j < length; j++)
      fprintf(file,"%1.17g\t" , GET_TRANSP(matrix, alength, i, j));
    fprintf(file,"\n");
  }
}

 /**
  * @brief      Imprime uma matriz sequncialmente
  *
  * @param      matrix  The matrix
  */
void printMatrixL(double **matrix, int length)
{
  int i,j=0;
  printf("%d\n", length);
  for (i = 0; i < length-1; ++i) {
    for (j = 0; j <= i; j++)
      printf("%1.17g\t" , GETT(matrix, i, j));
    printf("\n");
  }
}

void printNormal(double **matrix, int length)
{
  int i, j;
  printf("%d\n",length);
  int alength = SIZE_OF_ALIGNED_LINE(length);
  for (i = 0; i < length; ++i) {
    for (j = 0; j < length; j++)
      printf("%1.17g\t" , GET(matrix, alength, i, j));
    printf("\n");
  }
}
void printTranspNormal(double **matrix, int length)
{
  int i, j;
  int alength = SIZE_OF_ALIGNED_LINE(length);
  printf("%d\n",length);
  for (i = 0; i < length; ++i) {
    for (j = 0; j < length; j++)
      printf("%1.17g\t" , GET_TRANSP(matrix, alength, i, j));
    printf("\n");
  }
}

void printIndexes(int *line_map, int length)
{
  int i;
  printf("Indexes: \n");

  for (i = 0; i < length; ++i)
    printf("%d, ", line_map[i]);

  printf("\n");
}
