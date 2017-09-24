#include <stdio.h>
#include <stdlib.h>
#include "../headers/partial_pivoting.h"
#include "../headers/double_operations.h"
#include "../headers/datatypes.h"

void initIndexArray(int *index_array, int length){
    int i = 0;
    for (i = 0; i < length; ++i)
        index_array[i] = i;
}

void pivot(t_matrix *M, int pos, int *index_array){
    int i, length;
    int max_line = index_array[pos];

    double max_num = GET(M, index_array[pos], pos);
    double aux;
    length = M->length;

    for (i = pos+1; i < length; ++i) {
        if((aux = GET(M, index_array[i], pos)) > max_num) {
            max_num = aux;
            max_line = i;
        }
    }
    // if(IS_ZERO(max_num))
    //     die(ERROR_ZERO_PIVOT);
    aux = index_array[pos];
    index_array[pos] = index_array[max_line];
    index_array[max_line] = aux;
}
