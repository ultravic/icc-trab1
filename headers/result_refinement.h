#include "datatypes.h"
#ifndef __RESULT_REFINAMENT__
#define __RESULT_REFINAMENT__

/* Definição */
t_matrix* resultRefinement(t_matrix *U, t_matrix *X, t_matrix *I);

/* Definição */
void createIdentity(t_matrix *I, int length);

#endif
