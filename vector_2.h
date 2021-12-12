#ifndef TUTO_VECTOR_2
#define TUTO_VECTOR_2

typedef enum dimension{One=1,Two=2,Three=3}dimension;

typedef struct vector_2{
    dimension dim;
    int* shape;
    double* values;
    void (*init)(struct vector_2*, dimension, int*);
    double* (*get_first)(struct vector_2*);
    double* (*get_last)(struct vector_2*);
    double* (*get_next)(double*);
    double* (*get_next_at_axis)(struct vector_2*,double*, dimension);
    double* (*get_element_at)(struct vector_2*, int*);
    double* (*get_last_at_axis)(struct vector_2*, dimension);
    int (*get_index)(int* indexes, int* shape);
    void (*print)(struct vector_2*);
    void (*clear_vector)(struct vector_2*);
    void (*to_string)(struct vector_2*);
}vector_2;

void configure_vector_2(vector_2* v);
vector_2* build_vector_2(dimension dim, int* shape);

#endif