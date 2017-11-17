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
		double * matrix; // matriz
	} t_matrix;

	/** @brief     Estrutura para guardar um conjunto de matrizes. */
	typedef struct {
		int length; 	// Largura das Matrizes
		int alength;	// Largura da linha alinhada
		double *A; 		// Matriz Original
		double *L; 		// Matriz de Multiplicadores
		double *U; 		// Matriz escalonada
		double *Y; 		// Matriz temporária (L*Y = B)
		double *X; 		// Matriz resultante (U*X = Y)
		double *R; 		// Matriz de resíduos
		double *I; 		// Matriz indentidade
		double *W; 		// Matriz novo X (A*W = R)
	} matrixPack;

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
		bool to_file; // tem arquivo para saida
	}param;


	/** @brief     Faz x^2
	  *
	 * @param      x     numero a ser elevado
	 */
	#define SQ(x) (x)*(x)

	#define CACHE_LINE 64
	#define DOUBLE_PER_CACHE_LINE (CACHE_LINE / sizeof(double))
	#define SIZE_OF_ALIGNED_LINE(L) (L)+(DOUBLE_PER_CACHE_LINE-((L)%DOUBLE_PER_CACHE_LINE))
	#define SIZE_OF_ALIGNED_MATRIX(L) (L)*(SIZE_OF_ALIGNED_LINE(L))

	/**
	 * @brief      Aloca memória
	 *
	 * @param      t     tipo de dado
	 * @param      n     unidades
	 *
	 * @return     uma região de memória
	 */
	#define ALLOC(M,t,n) {int g = posix_memalign((void **)&(M),CACHE_LINE,(n)*sizeof(t)); g++;}


// INICIALIZAÇÔES

	/**
	 * @brief      Inicializa uma matriz
	 *
	 * @param      M     matriz a ser inicializada
	 */
	#define INIT_MATRIX(M) { \
		ALLOC(M,t_matrix,1); \
	}

	/**
	 * @brief      Calcula tamanho de uma matriz triangular
	 *
	 * @param      n     tamanho da maior linha
	 *
	 * @return   	O tamanho calculado
	 */
	#define TRIANGLE_SIZE(n) (int)(((1 + (n)) * (n)) / 2)

	/**
	 * @brief      Aloca memória para um conjunto de Matrizes
	 *
	 * @param      M     Conjunto de matrizes
	 */
	#define INIT_MATRIX_PACK(M) { \
		ALLOC(M.L,double,SIZE_OF_ALIGNED_MATRIX(M.length));	\
		ALLOC(M.U,double,SIZE_OF_ALIGNED_MATRIX(M.length));	\
		ALLOC(M.Y,double,SIZE_OF_ALIGNED_MATRIX(M.length));	\
		ALLOC(M.X,double,SIZE_OF_ALIGNED_MATRIX(M.length));	\
		ALLOC(M.R,double,SIZE_OF_ALIGNED_MATRIX(M.length));	\
		ALLOC(M.I,double,SIZE_OF_ALIGNED_MATRIX(M.length));	\
		ALLOC(M.W,double,SIZE_OF_ALIGNED_MATRIX(M.length));	\
	}


	#define FREE_MATRIX_PACK(M) { \
		free(M.A);	\
		free(M.L);	\
		free(M.U);	\
		free(M.Y);	\
		free(M.X);	\
		free(M.R);	\
		free(M.I);	\
		free(M.W);	\
	}


	/**
	 * @brief      Inicializa a estrutura dos parametros
	 *
	 * @param      P     estrutura dos parametros
	 */
	#define INIT_PARAM(P) { \
		P.K = 0; \
		P.N = 0; \
		P.in_file = "stdin"; \
		P.out_file = "stdout"; \
		P.random = false; \
		P.to_file = false; \
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
	 * @param      M       Matriz
	 * @param      length  Largura da matriz
	 * @param      l       Linha
	 * @param      c       Coluna
	 *
	 * @return     O valor acessado
	 */
	#define GET(M,length,l,c) ((*M)[(l) * (length) + (c)])
	#define GET_TRANSP(M,length,l,c) ((*M)[(c) * (length) + (l)])
	#define GETT(M,l,c) ((*M)[((((l)*((l)+1))/2)+(c))])

	/**
	 * @brief      Retorna um valor na matriz
	 *
	 * @param      M       Matriz
	 * @param      length  Largura da matriz
	 * @param      l       Linha
	 * @param      c       Coluna
	 * @param      v       valor a ser guardado
	 *
	 * @return     { description_of_the_return_value }
	 */
	#define SET(M,length,l,c,v) ((*M)[(l) * (length) + (c)] = (v))
	#define SET_TRANSP(M,length,l,c,v) ((*M)[(c) * (length) + (l)] = (v))
	#define SETT(M,l,c,v) ( (*M)[ ((((l)*((l)+1))/2)+(c)) ] = (v))


#endif
