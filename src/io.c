#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../headers/io.h"

/**
 * @brief      Le uma matriz n*n
 *
 * @param      M          Matriz onde serão guardados os valores lidos
 * @param      file_path  Arquivo a ser lido, ou "stdin"
 *
 * @return     0 Caso tenha sucesso
 */
int readMatrix(t_matrix * M, char *file_path){
	FILE *file;
	int i = 0; // contador de valores
	int c = 0;
	int size;

	if (strcmp(file_path, "stdin") == 0)
		file = stdin;
	else
		file = fopen(file_path, "r");


 	if (file)
 	{
		if(fscanf(file, "%d\n", &M->length) == ERROR)
			return ERROR;

		M->matrix = ALLOC(double,SQ(M->length));
		size = SQ(M->length);

		for (i = 0; i < size; ++i)
			c = fscanf(file, "%lf ", &M->matrix[i]);

		fclose(file);

		if (c != 1)
			return ERROR;

		return SUCCESS;
	};

	return ERROR;
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

