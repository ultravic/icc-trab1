/**
 * @file       datatypes.h
 * @author     Pedro Luiz de Souza Moreira  GRR20163064
 * @author     Victor Picussa   GRR20163068
 * @date       24 Sep 2017
 * @brief      Esse arquivo contém as estruturas de dados principais usadas
 *             durante o programa, bem como algumas macros uteis
 */

#include "error_handler.h"
#include <stdbool.h>
#include <stdlib.h>
#ifndef __DATATYPES__
#define __DATATYPES__

	/** @brief     Estrutura para matrizes de ponto fluntuante de precisão dupla */
	typedef struct {
		int length; // largura de uma linha da matriz
		double * matrix; // matriz
	} t_matrix;

	/** @brief     Estrutura para guardar variaveis da soma de kahan */
	typedef struct {
	    double c; // compensação
	    double sum; // soma
	} t_kahan;

	/** @brief     Estrutura para guardar os parametros lidos na execução */
	typedef struct{
		int K; // numero de iterações
		int N; // tamanho caso randomico
		char *in_file; // arquivo de entrada
		char *out_file; // arquivo de saída
		bool random; // random
	}param;


	/** @brief     Faz x^2
	  *
	 * @param      x     numero a ser elevado
	 */
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

	/**
	 * @brief      Inicializa uma matriz
	 *
	 * @param      M     matriz a ser inicializada
	 */
	#define INIT_MATRIX(M) { \
		M = ALLOC(t_matrix,1); \
		M->length = 0; \
	}

	/**
	 * @brief      Inicializa a estrutura dos parametros
	 *
	 * @param      P     estrutura dos parametros
	 */
	#define INIT_PARAM(P) { \
		P = ALLOC(param,1); \
		P->K = 0; \
		P->N = 0; \
		P->in_file = "stdin"; \
		P->out_file = "stdout"; \
		P->random = false; \
	}

	/**
	 * @brief      Inicializa a estrutura auxiliar da soma de kahan
	 *
	 * @param      K     estrutura auxiliar da soma de kahan
	 */
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

	/**
	 * @brief      Retorna um valor na matriz
	 *
	 * @param      M     Matriz
	 * @param      l     Linha
	 * @param      c     Coluna
	 * @param      v     valor a ser guardado
	 *
	 */
	#define SET(M,l,c,v) (M->matrix[(l) * M->length + (c)] = (v))


#endif
