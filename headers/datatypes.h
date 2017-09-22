#ifndef __DATATYPES__
#define __DATATYPES__

	/** @brief     Estrutura para matrizes de ponto fluntuante de precisão dupla */
	typedef struct {
		int length; // size
		double * matrix; // matrix
	} t_matrix;

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
