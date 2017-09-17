#include <stdlib.h>

double *generateSquareRandomMatrix(unsigned int n)
{
  double *mat = NULL;

  /* return NULL if memory allocation fails */
  if (!(mat = (double *)malloc(n*n*sizeof(double))))
    return NULL;

  /* generate a randomly initialized matrix in row-major order */
  double *ptr = mat;
  double *end = mat + (n * n);

  double invRandMax = 1.0/(double)RAND_MAX;

  while(ptr != end) {
    *ptr++ = (double)rand() * invRandMax;
  }

  return mat;
}
