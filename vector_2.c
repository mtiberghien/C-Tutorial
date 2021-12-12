#include <stdlib.h>
#include "vector_2.h"
#include <stdio.h>

double* init_array(int length)
{
    return (double*)calloc(length, sizeof(double));
}

void init_vector_2(vector_2* v, dimension dim, int* shape)
{
    v->dim = dim;
    v->shape = shape;
    switch(dim)
    {
        case Two: v->values = init_array(shape[0]*shape[1]);break;
        case Three: v->values = init_array(shape[0]*shape[1]*shape[2]); break;
        default:v->values = init_array(shape[0]);break;
    }
}

double* get_first_vector_2(vector_2* v)
{
    return v->values;
}

double* get_next_vector_2(double* iterator)
{
    return iterator+1;
}

double* get_next_vector_2_at_axis_1D(vector_2* v, double* iterator, dimension axis)
{
    return get_next_vector_2(iterator);
}

double* get_next_vector_2_at_axis_2D(vector_2* v, double* iterator, dimension axis)
{
    switch (axis)
    {
        case One: return iterator+v->shape[1];
        default: return get_next_vector_2(iterator);
    }
}

double* get_next_vector_2_at_axis_3D(vector_2* v, double* iterator, dimension axis)
{
    switch (axis)
    {
        case One: return iterator+(v->shape[1]*v->shape[2]);
        case Two: return iterator+v->shape[2];
        default: return get_next_vector_2(iterator);
    }
}

double* get_last_vector_1D(vector_2* v)
{
    return v->values+(v->shape[0]-1);
}

double* get_last_vector_2D(vector_2* v)
{
    return v->values+((v->shape[0]*v->shape[1])-1);
}

double* get_last_vector_3D(vector_2* v)
{
    return v->values+((v->shape[0]*v->shape[1]*v->shape[2])-1);
}

int get_index_1D(int* indexes, int* shape)
{
    return indexes[0];
}

int get_index_2D(int* indexes, int* shape)
{
    return shape[1]*indexes[0] + indexes[1];
}

int get_index_3D(int* indexes, int* shape)
{
    return shape[2]*shape[1]*indexes[0]+get_index_2D(indexes+1, shape+1);
}

double* get_vector_2_element_at(vector_2*v, int* indexes)
{
    return (v->values + v->get_index(indexes, v->shape));
}

double* get_last_vector_2_at_axis_1D(vector_2* v, dimension axis)
{
    return v->get_last(v);  
}

double* get_last_vector_2_at_axis_2D(vector_2* v, dimension axis)
{
    switch(axis)
    {
        case One: return get_vector_2_element_at(v,(int[]){v->shape[0]-1, 0});
        default: return v->get_last(v);
    }
}

double* get_last_vector_2_at_axis_3D(vector_2* v, dimension axis)
{
    switch(axis)
    {
        case One: return get_vector_2_element_at(v,(int[]){v->shape[0]-1, 0,0});
        case Two: return get_vector_2_element_at(v,(int[]){v->shape[0]-1, v->shape[1]-1,0});
        default: return v->get_last(v);
    }  
}

void clear_vector_2(vector_2* v)
{
    free(v->values);
    v->shape=NULL;
    v->values=NULL;
}

void get_sub_element(const vector_2* v, vector_2* sub_element, double* iterator)
{
    sub_element->dim = v->dim-1;
    sub_element->shape=(v->shape+1);
    sub_element->values=iterator;
    configure_vector_2(sub_element);
}

void print_1D(vector_2* v)
{
    printf("[");
    double* last= v->get_last(v);
    for(double* i=v->get_first(v);i<=last;i=v->get_next(i))
    {
        printf("%.2lf", *i);
        if(i!=last)
        {
            printf(", ");
        }
    }
    printf("]");
}

void print_2D(vector_2* v)
{
    printf("[");
    double* last = v->get_last_at_axis(v, One);
    for(double* i=v->get_first(v);i<=last;i=v->get_next_at_axis(v,i, One))
    {
        vector_2 v1;
        v->get_sub_element(v,&v1, i);
        print_1D(&v1);
        if(i!=last)
        {
            printf(",\n");
        }
    }
    printf("]");
}

void print_3D(vector_2* v)
{
    printf("[");
    double* last = v->get_last_at_axis(v,One);
    for(double* i=v->get_first(v);i<=last;i=v->get_next_at_axis(v,i, One))
    {
        vector_2 v2;
        v->get_sub_element(v,&v2,i);
        print_2D(&v2);
        if(i!=last)
        {
            printf(",\n");
        }
    }
    printf("]");
}

void to_string_vector_2(vector_2* v)
{
    v->print(v);
    printf("\n");
}

void configure_vector_2_1D(vector_2* v)
{
    v->get_last = get_last_vector_1D;
    v->print=print_1D;
    v->get_next_at_axis = get_next_vector_2_at_axis_1D;
    v->get_last_at_axis=get_last_vector_2_at_axis_1D;
    v->get_index=get_index_1D;
}

void configure_vector_2_2D(vector_2* v)
{
    v->get_last = get_last_vector_2D;
    v->print=print_2D;
    v->get_next_at_axis = get_next_vector_2_at_axis_2D;
    v->get_last_at_axis=get_last_vector_2_at_axis_2D;
    v->get_index=get_index_2D;
}

void configure_vector_2_3D(vector_2* v)
{
    v->get_last = get_last_vector_3D;
    v->print=print_3D;
    v->get_next_at_axis = get_next_vector_2_at_axis_3D;
    v->get_last_at_axis=get_last_vector_2_at_axis_3D;
    v->get_index=get_index_3D;
}

void configure_vector_2(vector_2* v)
{
    switch(v->dim)
    {
        case Two: configure_vector_2_2D(v);break;
        case Three: configure_vector_2_3D(v);break;
        default: configure_vector_2_1D(v);break;
    }
    v->get_first=get_first_vector_2;
    v->get_next=get_next_vector_2;
    v->clear_vector=clear_vector_2;
    v->get_element_at = get_vector_2_element_at;
    v->to_string = to_string_vector_2;
    v->get_sub_element=get_sub_element;
}

vector_2* build_vector_2(dimension dim, int* shape)
{
    vector_2* result = (vector_2*)malloc(sizeof(vector_2));
    init_vector_2(result, dim, shape);
    configure_vector_2(result);
    return result;
}