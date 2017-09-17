#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "headers/gauss_elimination.h"
#include "headers/matrix_generator.h"
#include "headers/datatypes.h"
#include "headers/io.h"


int main(int argc, char const *argv[])
{
	static const char PARAM_ERROR[] = "Parametros inválidos!\n Favor usar:invmat [-i arquivo_entrada] [-o arquivo_saida] [-r N] -i k \n";
	char *in_file, *out_file;
	in_file = "stdin";
	out_file = "stdout";
	int K = 0;
	int N = 0;

	if (!(argc >= 2 && (argc % 2 == 0))
	{
		fprintf(stderr,PARAM_ERROR);
		exit(FAILURE);
	} else
	{

		for (int i = 0; i < argc; ++i)
		{
			switch (argv[i])
			{
				case '-i': //Input file ou iterações?
					if (argv[++i] == argc)
					{
						K = atoi(argv[i]);
					} else
					{
						in_file = (char *) argv[i];
					}
				break;
				case '-o': //output file?
						out_file = (char *) argv[++i];
				break;
				case '-r': // random?
					#ifndef RANDOM
					#define RANDOM 1
					#else RANDOM 0
					#endif
					N = atoi(argv[++i]);
				break;
				default
					fprintf(stderr,PARAM_ERROR);
					exit(FAILURE);
			}
		}

		// Tudo certo com os parametros, prosseguindo

		// inicializa matriz A
		t_matrix *A;
		INIT_MATRIX(A);

		#ifdef RANDOM
			A->matrix = generateSquareRandomMatrix(A->lenght);
		#else
			if(readMatrix(A,file) == ERROR){
				printf("Erro! Não foi possível ler a entrada.\n");
				return ERROR;
			}
		#endif
		printMatrix(A);

	}

	return SUCCESS;
}

