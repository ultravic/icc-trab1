#include <stdio.h>
#include "../headers/result_refinament.h"
#include "../headers/datatypes.h"

t_matrix createIdentity(t_matrix *I, int size) {
	int i, j;

	t_matrix identity;
 	INIT_MATRIX(&identity);

	identity.length = size;
	identity.matrix = ALLOC(double, SQ(identity.length));

	for (i = 0; i < identity.length; ++i)
		for (j = i + 1; j < identity.length; ++j)
			I->matrix[i*identity.length + j] = 0;

	for (i = 0; i < identity.length; ++i)
		I->matrix[i*identity.length + i] = 1;

	return identity;
}

double calculateLC(t_matrix *U, t_matrix *X, int line, int column) {
  int i;
  double temporary = 0;
  for (i = 0; i < U->length; ++i)
    temporary += U->matrix[line*U->length + i] + X->matrix[i*X->length + column];

  return temporary;
}

t_matrix resultRefinament(t_matrix *U, t_matrix *X, t_matrix *I) {
  t_matrix residue;
  INIT_MATRIX(residue);

  residue = createIdentity();

  int i, j;
  for (i = 0; i < residue.length; ++i)
    for (j = 0; j < residue.length; ++j)
      residue[i*residue.length + j] -= calculateLC(U, X, i, j);

  return residue;
}
