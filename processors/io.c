#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "headers/io.h"

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
	int c;
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

/**
 * @brief      Imprime a matriz no formato especificado
 *
 * @param      M     Matriz a ser impressa
 */
void printMatrix(t_matrix *M){
	int length = M->length;
	printf("%d\n",length);
	for (int i = 0; i < length; ++i)
	{
		for (int j = 0; j < length; j++) {
			printf("%.17g " , VALUE(M,i,j));
		};
		printf("\n");
	}
}



