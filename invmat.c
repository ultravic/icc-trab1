#include <stdlib.h>
#include <stdio.h>
#include "headers/data_structures.h"
#include "headers/io.h"

int main(int argc, char const *argv[])
{
    char *file;
    if (!argv[1]) {
        file = "stdin";
    } else {
        file = (char *)argv[1];
    }

    t_matrix *A;
    INIT_MATRIX(A);

    if(readMatrix(A,file) == ERROR){
        printf("Erro! Não foi possível ler a entrada.\n");
        return ERROR;
    }
    printMatrix(A);
    return SUCCESS;
}