#include "template.h"

typedef struct NAME
{
    int n; 
    int cap; 
    TYPE *arr;
}
NAME;

void CONCAT(NAME, init) (NAME *vec);
void CONCAT(NAME, destroy) (NAME *vec);
int CONCAT(NAME, push) (NAME *vec, TYPE value);
TYPE CONCAT(NAME, pop) (NAME *vec);
void CONCAT(NAME, reserve) (NAME *vec, int capacity);
void CONCAT(NAME, resize) (NAME *vec, int newCnt, TYPE fill);
void CONCAT(NAME, insert) (NAME *vec, int where, TYPE *array, int num);
void CONCAT(NAME, erase) (NAME *vec, int where, int num);

#undef TYPE
#undef NAME