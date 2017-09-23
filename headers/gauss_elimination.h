#include "datatypes.h"
#ifndef __GAUSS_ELIMINATION__
#define __GAUSS_ELIMINATION__


/* Definição */
void gaussElimination(t_matrix *mA, t_matrix *mB, t_matrix *mL, int *index_change);

/* Definição */
void initMatrixL(t_matrix *matrixL, int length);

#endif
