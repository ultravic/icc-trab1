#include "datatypes.h"
#ifndef __GAUSS_ELIMINATION__
#define __GAUSS_ELIMINATION__


/* Definição */
void gaussElimination(t_matrix *matrix, t_matrix *matrixL, int *index_change);

/* Definição */
void initMatrixL(t_matrix *matrixL, int length);

#endif
