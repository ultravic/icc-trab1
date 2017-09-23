#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "../headers/gauss_elimination.h"
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

	// inicializa matriz A
	t_matrix *A, *L;
	INIT_MATRIX(A);
	INIT_MATRIX(L);

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

	printMatrix(A);
	printf("\n");
	L = gaussElimination(A);
	printMatrix(A);
	printf("\n");
	printMatrixL(L);

	return SUCCESS;
}
