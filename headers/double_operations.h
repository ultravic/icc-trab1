#include "datatypes.h"
#ifndef __DOUBLE_OPERATIONS__
#define __DOUBLE_OPERATIONS__

#define DBL_ZERO 10e-7

#define IS_ZERO(NUM) (NUM) < DBL_ZERO

#define KAHAN_SUM(K, input){ \
    double _y,_t; \
    _y = (input) - K->c; \
    _t = K->sum + _y; \
    K->c = (_t - K->sum) - _y; \
    K->sum = _t; \
}

#endif