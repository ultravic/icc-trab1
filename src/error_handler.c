#include <stdio.h>
#include <stdlib.h>
#include "../headers/error_handler.h"

void die(char const reason[]){
    fprintf(stderr, "%s", reason);
    exit(EXIT_FAILURE);
}
