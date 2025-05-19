#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include "template.h"

void CONCAT(NAME, init) (NAME *vec)
{
    vec->n = 0;
    vec->cap = 2;
    vec->arr = (TYPE*)calloc(sizeof(TYPE), vec->cap);
}

void CONCAT(NAME, destroy) (NAME *vec)
{
    free(vec->arr);
    memset(vec, 0, sizeof(*vec));
}

int CONCAT(NAME, push) (NAME *vec, TYPE value)
{
    if (vec->n == vec->cap)
    {
        vec->cap = vec->cap * 2 + 1;
        vec->arr = realloc(vec->arr, vec->cap * sizeof(vec->arr[0]));
    }
    int idx = (vec->n)++;
    vec->arr[idx] = value;
    return idx;
}

TYPE CONCAT(NAME, pop) (NAME *vec)
{
    assert(vec->n > 0);
    vec->n--;
    return vec->arr[vec->n];
}

void CONCAT(NAME, reserve) (NAME *vec, int capacity)
{
    if (capacity > vec->cap)
    {
        vec->cap = 2 * vec->cap + 1;
        if (vec->cap < capacity)
        {
            vec->cap = capacity;
        }
        vec->arr = realloc(vec->arr, vec->cap * sizeof(vec->arr[0]));
    }
}

void CONCAT(NAME, resize) (NAME *vec, int newSize, TYPE fill)
{
    assert(newSize >= 0);
    CONCAT(NAME, reserve)(vec, newSize);
    while (vec->n < newSize)
    {
        vec->arr[vec->n++] = fill;
    }
    vec->n = newSize;
}

void CONCAT(NAME, insert) (NAME *vec, int where, TYPE *arr, int num)
{
    assert(num >= 0);
    assert(where >= 0 && where <= vec->n);
    CONCAT(NAME, reserve)(vec, vec->n + num);
    memmove(vec->arr + where + num, vec->arr + where, (vec->n - where) * sizeof(vec->arr[0]));
    memcpy(vec->arr + where, arr, num * sizeof(vec->arr[0]));
    vec->n += num;
}

void CONCAT(NAME, erase) (NAME *vec, int where, int num)
{
    assert(where >= 0 && where <= vec->n);
    assert(num >= 0 && where + num <= vec->n);
    memmove(vec->arr + where, vec->arr + where + num, (vec->n - where - num) * sizeof(vec->arr[0]));
    vec->n -= num;
}

#undef NAME
#undef TYPE
