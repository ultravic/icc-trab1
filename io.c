// #include "io.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

typedef struct {
	int length; // size
	double * matrix; // matrix
} t_matrix;

#ifndef _IO_HEADER

	/** @brief     Faz x^2 */
	#define SQ(x) ((x)*(x))

	/**
	 * @brief      Aloca memória
	 *
	 * @param      t     tipo de dado
	 * @param      n     unidades
	 *
	 * @return     uma região de memória
	 */
	#define ALLOC(t,n) (t *) malloc((n)*sizeof(t))

	/** @brief     Erro de leitura */
	#define READ_ERROR -1

	/** @brief    Numero do STDIN */
	#define STDIN_FILENO 0

#endif


/**
 * @brief      Le uma matriz n*n 
 *
 * @return     Matriz[n*n], ou NULL caso ocorra ERRO na leitura
 */
double * readMatrix(){
	t_matrix M;
	M.length = (int) getc(stdin);	
	M.matrix = ALLOC(double,length);
	int n;

	while ((n = read(STDIN_FILENO, M.matrix, sizeof(double))) > 0)
	if (n == READ_ERROR){
		printf("Erro! Não é possível ler a matriz. \n");
		return NULL;
	}
	return matrix;
} 

void printMatrix(){
	for (int i = 0; i < count; ++i)
	{
		/* code */
	}
}


int main(int argc, char const *argv[])
{
	double *A;
	if(!(A = readMatrix()))
		return -1;
	printf("ok\n");
	return 0;
}