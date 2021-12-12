#include <stdlib.h>
#include "vector.h"

void init_vector(vector* v, int size)
{
    v->size = size;
    v->values = (int*)calloc(size, sizeof(int));
}

int* get_first(vector* v)
{
    return v->values;
}

int* get_next(int* iterator)
{
    return (iterator+1);
}

int* get_last(vector* v)
{
    return v->values+(v->size-1);
}

void clear_vector(vector* v)
{
    free(v->values);
    v->values=NULL;
    v->size=0;
}

vector* build_vector(int size)
{
    vector* result = (vector*)malloc(sizeof(vector));
    result->init=init_vector;
    result->get_first=get_first;
    result->get_last=get_last;
    result->get_next=get_next;
    result->clear_vector=clear_vector;
    result->init(result, size);
    return result;
}