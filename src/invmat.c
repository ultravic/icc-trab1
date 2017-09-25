/**
 * @file invmat.c
 * @author     Pedro Luiz de Souza Moreira  GRR20163064
 * @author     Victor Picussa   GRR20163068
 * @date       24 Sep 2017
 * @brief      Esse arquivo contém a função principal do programa, que inverte
 *             uma matriz, e faz o refinamento do resultado
 */

#include "../lib/datatypes.h"
#include "../lib/io.h"
#include "../lib/time_measurement.h"
#include "../lib/gauss_elimination.h"
#include "../lib/matrix_generator.h"
#include "../lib/matrix_solver.h"
#include "../lib/partial_pivoting.h"
#include "../lib/result_refinement.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>


int main(int argc, char const *argv[]) {
  // Inicializa struct de parametros
  param *P;
	INIT_PARAM(P);

  // Trata parametros
  int t;
  #ifndef DEBUG
    if((t = parseParameters(argc,argv,P)) != SUCCESS){
      die(ERROR_PARAM);
      return ERROR;
    }
  #else
    P->random = true;
  #endif


  // inicializa todas as matrizes necessárias e ponteiros
  t_matrix *mA, *mL, *mB, *mX, *mXW, *mI;

	INIT_MATRIX(mA);
	INIT_MATRIX(mL);
	INIT_MATRIX(mB);
	INIT_MATRIX(mX);
  INIT_MATRIX(mXW);
	INIT_MATRIX(mI);


  if (P->random) {
    // Caso tenha entrado com o parametro "-r" gera matriz aleatŕoia
    #ifndef DEBUG
      mA->length = P->N = 3;
    #else
      mA->length = P->N;
    #endif

    //srand( 20172 );
    mA->matrix = generateSquareRandomMatrix(P->N);
  } else {
    //  Caso contrário le a matriz
    printf("%s\n", P->in_file);
    if (readMatrix(mA, P->in_file) == ERROR) {
      printf("Erro! Não foi possível ler a entrada.\n");
      return ERROR;
    }
  }
  initMatrixIdentity(mI, mA->length);
  initMatrixL(mL, mA->length);


  // inicializa Vetor de Troca de Linhas
  int *index_array;
  index_array = ALLOC(int, P->N);
  initIndexArray(index_array, P->N);

  // começa processo de inversão e refinamento
	// inicializa o B copiando I
	mB->length = mA->length;
	mB->matrix = ALLOC(double, SQ(mA->length));
	memcpy(mB->matrix, mI->matrix, sizeof(double)*SQ(mA->length));

	printMatrix(mA, index_array);
	printf("\n");
	printMatrix(mB, index_array);
	printf("\n");
	printNormal(mI);
	printf("\n");
	gaussElimination(mA, mB, mL, index_array);
	printMatrix(mA, index_array);
	printf("\n");
	printMatrix(mB, index_array);
	printf("\n");
	printMatrixL(mL);
	printf("\n");

  mX->length = mA->length;
  mX->matrix = ALLOC(double, SQ(mA->length));

  mXW->length = mA->length;
	mXW->matrix = ALLOC(double, SQ(mA->length));

	// a cada iteração é feito o refinamento
  backwardSubstitution(mA, mB, mX, index_array, 'A');
  memcpy(mXW->matrix, mX->matrix, sizeof(double)*SQ(mA->length));
	while (P->K > 0) {
    memcpy(mX->matrix, mXW->matrix, sizeof(double)*SQ(mA->length));
    resultRefinement(mA, mXW, mI, mB, index_array);
    printf("B\n");
    printNormal(mB);
    printf("\n");
    backwardSubstitution(mA, mB, mXW, index_array, 'N');
    sumMatrix(mX, mXW);
  	memcpy(mB->matrix, mI->matrix, sizeof(double)*SQ(mA->length));
    P->K--;
	}

  printf("X=\n");
  printNormal(mXW);
  printf("\n");

  free(mA->matrix);
  free(mA);
  free(mB->matrix);
  free(mB);
  free(mI->matrix);
  free(mI);
  free(mL->matrix);
  free(mL);
  free(mX->matrix);
  free(mX);

  return SUCCESS;
}
