#include "error_handler.h"
#include <stdbool.h>
#ifndef __DATATYPES__
#define __DATATYPES__

	/** @brief     Estrutura para matrizes de ponto fluntuante de precisão dupla */
	typedef struct {
		int length; // largura de uma linha da matriz
		double * matrix; // matriz
	} t_matrix;

	typedef struct {
	    double c; // compensação
	    double sum; // soma
	} t_kahan;

	typedef struct{
		int K; // numero de iterações
		int N; // tamanho caso randomico
		char *in_file; // arquivo de entrada
		char *out_file; // arquivo de saída
		bool random; // random
	}param;


	/** @brief     Faz x^2 */
	#define SQ(x) (x)*(x)

	/**
	 * @brief      Aloca memória
	 *
	 * @param      t     tipo de dado
	 * @param      n     unidades
	 *
	 * @return     uma região de memória
	 */
	#define ALLOC(t,n) (t *) malloc((n)*sizeof(t))


// INICIALIZAÇÔES
	#define INIT_MATRIX(M) { \
		M = ALLOC(t_matrix,1); \
		M->length = 0; \
	}

	#define INIT_PARAM(P) { \
		P = ALLOC(param,1); \
		P->K = 0; \
		P->N = 0; \
		P->in_file = "stdin"; \
		P->out_file = "stdout"; \
		P->random = false; \
	}

	#define INIT_KAHAN(K) { \
	    K->c = 0.0; \
	    K->sum = 0.0;\
	}

	/**
	 * @brief      Retorna um valor na matriz
	 *
	 * @param      M     Matriz
	 * @param      l     Linha
	 * @param      c     Coluna
	 *
	 * @return     O valor acessado
	 */
	#define GET(M,l,c) (M->matrix[(l) * M->length + (c)])
	#define GETV(M,i) (M->matrix[(i)])

	#define SET(M,l,c,v) (M->matrix[(l) * M->length + (c)] = (v))
	#define SETV(M,i,v) (M->matrix[(i)] = (v))

	/** @brief     Erro */
	#define ERROR -1

	/** @brief    Sucesso */
	#define SUCCESS 0

	/** @brief     Zero em ponto fluntuante */
	#define ZEROF 0.0f

#endif
