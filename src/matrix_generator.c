#include "../headers/datatypes.h"
#include <stdlib.h>

double *generateSquareRandomMatrix(int n)
{
  double *mat = NULL;

  /* return NULL if memory allocation fails */
  if (!(mat = ALLOC(double, SQ(n))))
    return NULL;

  /* generate a randomly initialized matrix in row-major order */
  double *ptr = mat;
  double *end = mat + SQ(n);

  double invRandMax = 1.0/(double)RAND_MAX;

  while(ptr != end) {
    *ptr++ = (double)rand() * invRandMax;
  }

  return mat;
}
