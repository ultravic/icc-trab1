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
#include <likwid.h>


int main(int argc, char const *argv[]) {
//----------------------------------------------------------------------
// Instanciações e Alocação de memoria
// ----------------------------------------------------------------------
  // Variaveis para temporização
  //----------------------------------------------------------------------
  // LIKWID_MARKER_INIT;

  double initial_time, actual_time, norm;
  double iter_time, residue_time, lu_time;
  iter_time = residue_time = lu_time = TRUE_ZERO;
  //----------------------------------------------------------------------

  // Arquivo de escrita
  FILE *output_file;

  // Estrutura para guardar os parametros
  param P;
  INIT_PARAM(P);

  // Trata parametros
  if(parseParameters(argc, argv, &P) != SUCCESS)
    die(ERROR_PARAM);

  // Conjunto de matrizes
   matrixPack M;
   M.length = 0;

  // Obtém matriz original
  //----------------------------------------------------------------------
  if (P.random) {
    // Gera matriz aleatória
    // M.length = 5;
    M.length = P.N;
    srand(20172);
    M.A = generateRandomSquareMatrix(M.length);
  } else {
    //  Le a matriz
    if (readMatrix(&M, P.in_file) == ERROR)
      die(ERROR_READING);
  }

  M.alength = SIZE_OF_ALIGNED_LINE(M.length);
  //----------------------------------------------------------------------
  // Aloca memória para as matrizes necessarias no processo
  INIT_MATRIX_PACK(M);

  // Gera uma matriz identidade
  M.I = generateIdentityMatrix(M.length);

  memcpy(M.L, M.I, SIZE_OF_ALIGNED_MATRIX(M.length)*sizeof(double));

//----------------------------------------------------------------------
// Inversão da Matriz
//----------------------------------------------------------------------
  // Inicializa vetor de mapeamento de linhas
  //----------------------------------------------------------------------
    int *line_map;
    line_map = generateLineMap(M.length);
  //----------------------------------------------------------------------

  //----------------------------------------------------------------------
  // Efetua a eliminação gaussiana com pivotamento parcial e fatoração LU
  //----------------------------------------------------------------------
    initial_time = timestamp();
      gaussElimination(&M.A, &M.L, &M.U, line_map, M.length);
    actual_time = timestamp();
    lu_time = actual_time - initial_time;
  //----------------------------------------------------------------------


  //----------------------------------------------------------------------
  // Inverte a Matriz
  //----------------------------------------------------------------------
    initial_time = timestamp();
      // LIKWID_MARKER_START("op1");
        // L*Y = B
        forwardSubstitution(&M.L, &M.Y, &M.I, line_map, M.length);
        // U*X = Y
        backwardSubstitution(&M.U, &M.X, &M.Y, line_map, M.length);
      // LIKWID_MARKER_STOP("op1");
    actual_time = timestamp();
    residue_time +=(actual_time - initial_time);
  //----------------------------------------------------------------------

  //----------------------------------------------------------------------
  // Verifica se tem arquivo para saida
  //----------------------------------------------------------------------
  if (P.to_file)
    output_file = fopen(P.out_file, "w");
  else
    output_file = stdout;

  fprintf(output_file, "#\n");
//----------------------------------------------------------------------

// printf("X---------\n");
printTranspNormal(&M.X, M.length);
// printf("---------\n");

//----------------------------------------------------------------------
// Refinamento
//----------------------------------------------------------------------
 int iter = 1;
  // memcpy(M.R, M.I, SQ(M.length)*sizeof(double));
 while(iter <= P.K){

    //----------------------------------------------------------------------
    // Calcula resíduo R = I - A*X
    //----------------------------------------------------------------------
      initial_time = timestamp();
        // LIKWID_MARKER_START("op2");
          residueCalc(&M.A, &M.X, &M.I, &M.R, M.length);
        // LIKWID_MARKER_STOP("op2");
      actual_time = timestamp();
      residue_time +=(actual_time - initial_time);
    //----------------------------------------------------------------------

    printTranspNormal(&M.R, M.length);
    //----------------------------------------------------------------------
    // Calcula norma L2 do resíduo
    //----------------------------------------------------------------------
      initial_time = timestamp();
        norm = normCalc(&M.R, M.length);
      actual_time = timestamp();
      iter_time += (actual_time - initial_time);
      fprintf(output_file, "# iter %d: %1.17g\n", iter, norm);
    //----------------------------------------------------------------------

    // Calcula novo S.L
    //----------------------------------------------------------------------
    initial_time = timestamp();

    // Efetua Aw = R

    // LIKWID_MARKER_START("op1");
      // L*Y = R
      forwardSubstitution(&M.L, &M.Y, &M.R, line_map, M.length);
      // U*W = Y
      backwardSubstitution(&M.U, &M.W, &M.Y, line_map, M.length);
    // LIKWID_MARKER_STOP("op1");

    // X+=W
    sumMatrix(&M.W, &M.X, M.length);

    printf("R---------\n");
    // printf("---------\n");

    actual_time = timestamp();
    residue_time +=(actual_time - initial_time);
    //----------------------------------------------------------------------

    iter++;
  }

  //----------------------------------------------------------------------
  // Calcula médias dos tempos
  //----------------------------------------------------------------------
  iter_time = (iter_time / iter);
  residue_time = (residue_time / iter);
  //----------------------------------------------------------------------

  //----------------------------------------------------------------------
  // Imprime os resultados
  //----------------------------------------------------------------------
  fprintf(output_file, "# Tempo LU: %lf\n", lu_time);
  fprintf(output_file, "# Tempo iter %lf\n", iter_time);
  fprintf(output_file, "# Tempo residuo: %lf\n", residue_time);
  fprintf(output_file, "#\n");
  //----------------------------------------------------------------------

  // printfTranspMapped(&M.X, line_map, output_file, M.length);

  //----------------------------------------------------------------------
  // Libera a memória do conjunto de matrizes
  //----------------------------------------------------------------------
  FREE_MATRIX_PACK(M);
  free(line_map);
  //----------------------------------------------------------------------

  //----------------------------------------------------------------------
  // Fecha arquivo de saída
  //----------------------------------------------------------------------
  fclose(output_file);
  //----------------------------------------------------------------------

  // LIKWID_MARKER_CLOSE;

  return SUCCESS;
}
