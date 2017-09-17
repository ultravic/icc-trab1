#ifndef _IO_
#define _IO_
#include "headers/data_structures.h"

    /**
     * @brief      Le uma matriz n*n
     *
     * @param      M          Matriz onde serão guardados os valores lidos
     * @param      file_path  Arquivo a ser lido, ou "stdin"
     *
     * @return     0 Caso tenha sucesso
     */
    int readMatrix(t_matrix * M, char *file_path);

    /**
     * @brief      Imprime a matriz no formato especificado
     *
     * @param      M     Matriz a ser impressa
     */
    void printMatrix(t_matrix *M);

#endif
