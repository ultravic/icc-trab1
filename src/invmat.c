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
	param *P;
	INIT_PARAM(P);

	// Trata parametros
	int t;
	if((t = parseParameters(argc, argv, P)) != SUCCESS){
		die(ERROR_PARAM);
		printf("error %d\n", t);
		return -1;
	}

	// Tudo certo com os parametros, prosseguindo

	//inicializa Vetor de Troca de Linhas
	int *index_array;
	INIT_ARRAY(index_array, P->N);
	initIndexArray(index_array, P->N);

	// inicializa todas as matrizes necessárias e ponteiros
	t_matrix *mA, *mL, *mB, *mX, *mI;

	INIT_MATRIX(mA);
	INIT_MATRIX(mL);
	INIT_MATRIX(mB);
	INIT_MATRIX(mX);
	INIT_MATRIX(mI);

	if(P->random) {
		mA->length = P->N;
		mA->matrix = generateSquareRandomMatrix(P->N);
		initMatrixIdentity(mI, P->N);
		initMatrixL(mL, P->N);
	} else {
		printf("%s\n", P->in_file );
		if(readMatrix(mA, P->in_file) == ERROR) {
			printf("Erro! Não foi possível ler a entrada.\n");
			return ERROR;
		}
		initMatrixIdentity(mI, mA->length);
		initMatrixL(mL, mA->length);
	}

	mB = mI;
	// while (k > 0) {
		printMatrix(mA);
		printf("\n");
		printMatrix(mI);
		printf("\n");
		gaussElimination(mA, mL, index_array);
		printMatrix(mA);
		printf("\n");
		printMatrixL(mL);

		// Matriz B recebe a matriz resíduo r = Identidade (I) - A (U). X'
		mB = mI;
		resultRefinement(mA, mX, mI, mB);
	// }

	return SUCCESS;
}
