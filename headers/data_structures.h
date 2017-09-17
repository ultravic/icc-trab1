#ifndef _DATA_STRUCTURES_
#define _DATA_STRUCTURES_

	/** @brief     Estrutura para matrizes de ponto fluntuante de precisão dupla */
	typedef struct {
		int length; // size
		double * matrix; // matrix
	} t_matrix;

	#ifndef _IO_HEADER

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

	/**
	 * @brief      Inicializa a struct da matriz
	 *
	 * @param      M     Matriz a ser inicializada
	 */
	#define INIT_MATRIX(M) { \
		M = ALLOC(t_matrix,1); \
		M->length = 0; \
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
	#define VALUE(M,l,c) (M->matrix[(l) * M->length + (c)])

	/** @brief     Erro de leitura */
	#define ERROR -1

	/** @brief     Erro de leitura */
	#define SUCCESS 0

#endif