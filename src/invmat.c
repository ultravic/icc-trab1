#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "../headers/partial_pivoting.h"
#include "../headers/gauss_elimination.h"
#include "../headers/result_refinement.h"
#include "../headers/matrix_generator.h"
#include "../headers/matrix_solver.h"
#include "../headers/datatypes.h"
#include "../headers/printers.h"
#include "../headers/io.h"

int main(int argc, char const *argv[])
{
	// Inicializa struct de parametros
	param Parameters,*P;
	P = &Parameters;
	INIT_PARAM(P);

	// Trata parametros
	int t;
	if((t = parseParameters(argc,argv,P)) != SUCCESS){
		die(ERROR_PARAM);
		printf("error %d\n", t);
		return -1;
	}

	// Tudo certo com os parametros, prosseguindo

	//inicializa Vetor de Troca de Linhas
	int *index_array;
	initIndexArray(index_array, P->N);

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

	// cria a identidade
	createIdentity(mI, P->N);

	if(P->random)
	{
		A.length = P->N;
		A.matrix = generateSquareRandomMatrix(P->N);
	} else
	{
		printf("%s\n",P->in_file );
		if(readMatrix(mA,P->in_file) == ERROR){
			printf("Erro! Não foi possível ler a entrada.\n");
			return ERROR;
		}
	}

	// while (k > 0) {
		printMatrix(mA);
		printf("\n");
		mL = gaussElimination(mA, index_array);
		printMatrix(mA);
		printf("\n");
		printMatrixL(mL);

		// Matriz B recebe a matriz resíduo r = Identidade (I) - A (U). X'
		mB = resultRefinement(mA, mX, mI);
	// }

	return SUCCESS;
}
