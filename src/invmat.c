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
  double initial_time, actual_time;
  double lu_time = TRUE_ZERO;

  double norm;
  FILE *file;

  // Inicializa struct de parametros
  param Parameters, *P;
  P = &Parameters;
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
  t_matrix A, L, B, X, I, *mA, *mL, *mB, *mX, *mI;

  mA = &A;
  mB = &B;
  mL = &L;
  mX = &X;
  mI = &I;

  INIT_MATRIX(mA);
  INIT_MATRIX(mL);
  INIT_MATRIX(mB);
  INIT_MATRIX(mX);
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


  // a cada iteração é feito o refinamento
  int iter = 0;

  // os timers usam soma de kahan
  t_kahan *iter_time,*residue_time;
  iter_time = ALLOC(t_kahan, 1);
  residue_time = ALLOC(t_kahan, 1);
  INIT_KAHAN(iter_time);
  INIT_KAHAN(residue_time);
  do{
    //inicia contagem do tempo
    initial_time = timestamp();
    // calcula o X
    mX = backwardSubstitution(mA, mB, index_array);

    // Matriz B recebe a matriz resíduo r = Identidade (I) - A (U). X'
    *(mB)->matrix = *(mI)->matrix;

    // Faz o refinamento
    resultRefinement(mA, mX, mI, mB, index_array);
    // Mede o tempo
    actual_time = timestamp();
    KAHAN_SUM(iter_time,(actual_time - initial_time));

    // Calculo da norma
    initial_time = timestamp();
    norm = calculateL2Norm(mB);
    actual_time = timestamp();
    KAHAN_SUM(residue_time,(actual_time - initial_time));

    fprintf(file, "# iter %d: %.17g\n", iter, norm);
    iter++;
  } while (iter <= P->K);

  printf("%d\n",iter );
  iter_time->sum = (iter_time->sum / iter);
  residue_time->sum = (residue_time->sum / iter);

  fprintf(file, "# Tempo LU: %lf\n", lu_time);
  fprintf(file, "# Tempo iter %lf\n", iter_time->sum);
  fprintf(file, "# Tempo residuo: %lf\n", residue_time->sum);
  fprintf(file, "#\n");
  printMatrix(mX,index_array,file);

  fclose(file);

  return SUCCESS;
}
