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
  double iter_time, residue_time, lu_time;
  int length;

  FILE *file;

  // Inicializa struct de parametros
  param *P;
  INIT_PARAM(P);

  // Trata parametros
  if(parseParameters(argc,argv,P) != SUCCESS){
    die(ERROR_PARAM);
  }

  // inicializa todas as matrizes necessárias e ponteiros
  t_matrix *mA, *mU, *mL, *mB, *mX, *mXW, *mI;

  INIT_MATRIX(mA);
  INIT_MATRIX(mL);
  INIT_MATRIX(mU);
  INIT_MATRIX(mB);
  INIT_MATRIX(mX);
  INIT_MATRIX(mXW);
  INIT_MATRIX(mI);

// Caso tenha entrado com o parametro "-r"
  if (P->random) {
    
    // Gera matriz aleatŕoia
    length = P->N;
    srand(20172 );
    mA->matrix = generateSquareRandomMatrix(length);
  
  } else {

    //  Le a matriz
    if (readMatrix(mA, &length, P->in_file) == ERROR) 
      die(ERROR_READING);

  }


  // inicializa uma matriz identidade
  initMatrixIdentity(mI, length);

  // inicializa matriz L
  initMatrixL(mL, length);

  // inicializa Vetor de Troca de Linhas
  int *index_array;
  index_array = ALLOC(int, length);
  initIndexArray(index_array, length);

  // começa processo de inversão e refinamento
  // inicializa o B copiando I
  mB->matrix = ALLOC(double, SQ(length));
  memcpy(mB->matrix, mI->matrix, sizeof(double)*SQ(length));

  // Efetua a eliminação gaussiana com pivotamento parcial e fatoração LU
  initial_time = timestamp();

  gaussElimination(mA, mL, mU, index_array, length);

  actual_time = timestamp();
  lu_time = actual_time - initial_time;


  // verifica se tem arquivo para saida
  if (P->to_file)
    file = fopen(P->out_file, "w");
  else
    file = stdout;

  fprintf(file, "#\n");

  // a cada iteração é feito o refinamento
  int iter = 1;

  // L*Y = B
  forwardSubstitution(L,Y,I);
  
  // U*X = Y
  backwardSubstitution(U,X,Y);
  

  while(iter <= K){

    //---------------------------------
    // Calcula resíduo R = I - A*X
    initial_time = timestamp();

    residueCalc(A, X, R, I);

    actual_time = timestamp();
    residue_time +=(actual_time - initial_time);

    //---------------------------------

    //---------------------------------
    // Calcula norma L2 do resíduo
    initial_time = timestamp();

    norm = calculateL2Norm(R);

    actual_time = timestamp();
    iter_time += (actual_time - initial_time);
    
    fprintf(file, "# iter %d: %.17g\n", iter, norm);
    //---------------------------------
    
    //---------------------------------
    initial_time = timestamp();

    //Pivotamento parcial em R
    ????
    // Efetua Aw = R

    // L*Y = R
    forwardSubstitution(L,Y,R);
    
    // U*X = Y
    backwardSubstitution(U,W,Y);

    // X+=W
    sumMatrix(W, X);
    actual_time = timestamp();
    residue_time +=(actual_time - initial_time);
    //---------------------------------
      
    iter++;

  }

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
