#include "datatypes.h"
#ifndef __RESULT_REFINAMENT__
#define __RESULT_REFINAMENT__

/* Definição */
t_matrix* resultRefinament(t_matrix *U, t_matrix *X, t_matrix *I);

/* Definição */
t_matrix createIdentity(t_matrix *I, int size);

#endif
