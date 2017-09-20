#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>
#include "../headers/gauss_elimination.h"
#include "../headers/matrix_generator.h"
#include "../headers/datatypes.h"
#include "../headers/printers.h"
#include "../headers/io.h"

typedef struct{
	int K; // numero de iterações
	int N; // tamanho caso randomico
	char *in_file; // arquivo de entrada
	char *out_file; // arquivo de saída
	bool random; // random
}param;

#define INIT_PARAM(P) { \
	P = ALLOC(param,1); \
	P->K = 0; \
	P->N = 0; \
	P->in_file = "stdin"; \
	P->out_file = "stdout"; \
	P->random = false; \
}

void die(char const reason[]){
	fprintf(stderr, "%s", reason);
	exit(EXIT_FAILURE);
}

int parseParameters(int argc, char const *argv[], param *P){
	int i;
	// Verifica se parametros tem chance de estarem no padrão
	if (!((argc >= 2) && (argc % 2 != 0)))
		return ERROR;
	else
	{
		// Trata parametros
		for (i = 1; i < argc && argv[i][0] == '-'; i++)
		{
			switch (argv[i][1])
			{
				case 'e': //Input file?
					i++;
					P->in_file = (char *) argv[i];
				break;
				case 'o': //output file?
			        i++;
					P->out_file = (char *) argv[i];
				break;
				case 'r': // random?
				    i++;
					P->random = true;
					P->N = atoi(argv[i]);
				break;
				case 'i': //iterações
					i++;
					P->K = atoi(argv[i]);
				break;
				default:
					return ERROR;
			}
		}
	}
	return SUCCESS;
}

int main(int argc, char const *argv[])
{
	static const char PARAM_ERROR[] = "Parametros inválidos!\n Favor usar:invmat [-i arquivo_entrada] [-o arquivo_saida] [-r N] -i k \n";


	// Trata parametros
	param *P;
	INIT_PARAM(P);

	int t;
	if((t = parseParameters(argc,argv,P)) != SUCCESS){
		die(PARAM_ERROR);
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
