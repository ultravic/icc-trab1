#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "../headers/gauss_elimination.h"
#include "../headers/result_refinament.h"
#include "../headers/matrix_generator.h"
#include "../headers/matrix_solver.h"
#include "../headers/datatypes.h"
#include "../headers/printers.h"
#include "../headers/io.h"

int main(int argc, char const *argv[])
{
	// Trata parametros
	param *P;
	INIT_PARAM(P);

	int t;
	if((t = parseParameters(argc,argv,P)) != SUCCESS){
		die(ERROR_PARAM);
		printf("error %d\n", t);
		return -1;
	}

	// Tudo certo com os parametros, prosseguindo

	// inicializa todas as matrizes necessárias
	t_matrix *A, *L, B, *X, index_array;
	INIT_MATRIX(A);
	INIT_MATRIX(L);
	B = INIT_STRUCT();
	INIT_MATRIX(X);
	index_array = INIT_STRUCT();

	// cria a identidade
	B = createIdentity(I, P->N);

	if(P->random)
	{
		A->length = P->N;
		A->matrix = generateSquareRandomMatrix(P->N);
	} else
	{
		printf("%s\n",P->in_file );
		if(readMatrix(A,P->in_file) == ERROR){
			printf("Erro! Não foi possível ler a entrada.\n");
			return ERROR;
		}
	}

	// while (k > 0) {
		printMatrix(A);
		printf("\n");
		L = gaussElimination(A, &index_array);
		printMatrix(A);
		printf("\n");
		printMatrixL(L);

		// Matriz B recebe a matriz resíduo r = Identidade (I) - A (U). X'
		B = resultRefinament(A, X, I);
	// }

	return SUCCESS;
}
