#include <stdio.h>
#include <stdlib.h>
#include "../headers/matrix_solver.h"
#include "../headers/datatypes.h"

/**
 * @brief      Efetua retrosubstituição de um sistema triangular sup
 *
 * @param      A     Uma Matriz triangular superior de coeficientes
 * @param      b     Um vetor de termos independentes
 *
 * @return     vetor com o valor calculado das incógnitas
 */
double * backwardSubstitution(t_matrix *A, double *b){

    int length = A->length;
    // Cria vetor de incógnitas
    double *x = ALLOC(double,length);
    // contadores
    int i,j;

    double sum;

    for (i = (length - 1); i > 0; --i){
        sum = b[i];

        for (j = (i+1); j < length; ++i)
        {
            sum = sum - (GET(A,i,j) * GETV(x,j)); // risco cancelamento subtrativo
            SETV(x,k,(sum/GET(A,i,i))); //risco overflow e div por 0
        }
    }
    return x;
}
