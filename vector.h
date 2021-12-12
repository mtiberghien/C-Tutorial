#ifndef TUTO_VECTOR
#define TUTO_VECTOR

typedef struct vector
{
    int size;
    int* values;
    void (*init)(struct vector*, int);
    int* (*get_first)(struct vector*);
    int* (*get_last)(struct vector*);
    int* (*get_next)(int*);
    void (*clear_vector)(struct vector*);
}vector;

vector* build_vector(int size);

#endif