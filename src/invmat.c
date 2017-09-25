  /**
 * @file invmat.c
 * @author     Pedro Luiz de Souza Moreira  GRR20163064
 * @author     Victor Picussa   GRR20163068
 * @date       24 Sep 2017
 * @brief      Esse arquivo contém a função principal do programa, que inverte
 *             uma matriz, e faz o refinamento do resultado
 */

#include "../lib/datatypes.h"
#include "../lib/double_operations.h"
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
  double initial_time, actual_time, norm;
  double lu_time = TRUE_ZERO;
  char type = 'A';
  FILE *file;

  // Inicializa struct de parametros
  param *P;
	INIT_PARAM(P);

  // Trata parametros
  #ifdef DEBUG
    P->random = true;
  #else
    if(parseParameters(argc,argv,P) != SUCCESS){
      die(ERROR_PARAM);
    }
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
    #ifdef DEBUG
      mA->length = P->N = 5;
    #else
      mA->length = P->N;
    #endif

    srand(20172 );
    mA->matrix = generateSquareRandomMatrix(P->N);
  } else {
    //  Caso contrário le a matriz
    if (readMatrix(mA, P->in_file) == ERROR) {
      die(ERROR_READING);
    }
  }



  // inicializa uma matriz identidade
  initMatrixIdentity(mI, mA->length);

  // inicializa matriz L
  initMatrixL(mL, mA->length);

  // inicializa Vetor de Troca de Linhas
  int *index_array;
  index_array = ALLOC(int, mA->length);
  initIndexArray(index_array, mA->length);

  // começa processo de inversão e refinamento
  // inicializa o B copiando I
  mB->length = mA->length;
  mB->matrix = ALLOC(double, SQ(mA->length));
  memcpy(mB->matrix, mI->matrix, sizeof(double)*SQ(mA->length));

  // Efetua a eliminação gaussiana
  initial_time = timestamp();
  gaussElimination(mA, mB, mL, index_array);
  actual_time = timestamp();
  lu_time = actual_time - initial_time;


  // verifica se tem arquivo para saida
  if (P->to_file)
    file = fopen(P->out_file, "w");
  else
    file = stdout;
  fprintf(file, "#\n");

  // aloca a matriz x
  mX->length = mA->length;
  mX->matrix = ALLOC(double, SQ(mA->length));

  mXW->length = mA->length;
	mXW->matrix = ALLOC(double, SQ(mA->length));

  // a cada iteração é feito o refinamento
  int iter = 0;

  // os timers usam soma de kahan
  t_kahan *iter_time,*residue_time;
  iter_time = ALLOC(t_kahan, 1);
  residue_time = ALLOC(t_kahan, 1);
  INIT_KAHAN(iter_time);
  INIT_KAHAN(residue_time);
  do {
    initial_time = timestamp();
    // calcula o X
    backwardSubstitution(mA, mB, mX, index_array, type);
    if(type == 'A'){
      memcpy(mXW->matrix, mX->matrix, sizeof(double)*SQ(mA->length));
    }
    else{
      memcpy(mX->matrix, mXW->matrix, sizeof(double)*SQ(mA->length));
      memcpy(mB->matrix, mI->matrix, sizeof(double)*SQ(mA->length));
    }
    resultRefinement(mA, mXW, mI, mB, index_array, type);
    sumMatrix(mX, mXW);
    // Mede o tempo
    actual_time = timestamp();
    KAHAN_SUM(iter_time,(actual_time - initial_time));
    type = 'N';

    // Calculo da norma
    initial_time = timestamp();
    norm = calculateL2Norm(mB);
    actual_time = timestamp();
    KAHAN_SUM(residue_time,(actual_time - initial_time));

    fprintf(file, "# iter %d: %.17g\n", iter, norm);
    iter++;

  } while(iter <= P->K);

  iter_time->sum = (iter_time->sum / iter);
  residue_time->sum = (residue_time->sum / iter);

  fprintf(file, "# Tempo LU: %lf\n", lu_time);
  fprintf(file, "# Tempo iter %lf\n", iter_time->sum);
  fprintf(file, "# Tempo residuo: %lf\n", residue_time->sum);
  fprintf(file, "#\n");

  printMatrix(mX,index_array,file);
  fclose(file);
  free(mA->matrix);
  free(mA);
  free(mL->matrix);
  free(mL);
  free(mB->matrix);
  free(mB);
  free(mX->matrix);
  free(mX);
  free(mI->matrix);
  free(mI);
  free(index_array);
  free(residue_time);
  free(iter_time);


  return SUCCESS;
}
