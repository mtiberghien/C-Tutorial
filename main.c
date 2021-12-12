#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "vector_2.h"
#include "vector.h"

void show_variable_from_address(char* header, int* i)
{
    printf("%s\n\tvalue:%d, address:%p\n", header, *i, i);
}

void show_variable(char* header, int i)
{
    show_variable_from_address(header, &i);
}

void increment_not_working(int i)
{
    i++;
    show_variable_from_address("Inside increment_1",&i);
}

int increment_concurrent(int i)
{
    return i+1;
}

void increment_with_pointer(int* i)
{
    (*i)++;
    show_variable_from_address("Inside increment_3",i);
}

//Understand variables and pointers
void exercice_1()
{
    int i;
    //i is a variable which type is int
    // sizeof show the size in bytes of a variable
    // &i is the address of the variable
    printf("%s\n\tvalue:%d, address:%p\n", "Inside exercice_1", i, &i);
    show_variable("Show_variable passing value",i);
    show_variable_from_address("Show_variable passing address", &i);
    increment_not_working(i);
    i=increment_concurrent(i);
    show_variable_from_address("After increment_2",&i);
    increment_with_pointer(&i);
}

void show_array_values(char* header, int* array, int size)
{
    for(int i=0;i<size;i++)
    {
        char index_header[20];
        sprintf(index_header,"Index %d of ", i);
        strcat(index_header, header);
        show_variable_from_address(index_header, array+i);
    }
}

//Understand arrays and pointers
void exercice_2()
{
    int array[3]={1,2,3};
    show_variable_from_address("Array address",array);
    show_variable_from_address("Second value address", &array[1]);
    show_variable_from_address("Array address + 2", array+2);
    int size = 3;
    int* array_2 = malloc(sizeof(int)*size);
    int* array_3 = calloc(size, sizeof(int));
    show_array_values("array_2", array_2, 3);
    show_array_values("array_3", array_3, 3);
    free(array_2);
    free(array_3);
}

//Understand structure pointer of functions and iterators
void exercice_3()
{
    vector* v = build_vector(3);
    int index=0;
    for(int* i=v->get_first(v);i<=v->get_last(v);i=v->get_next(i))
    {
        (*i)=index+1;
        char header[10];
        sprintf(header,"Index %d",index++);
        show_variable_from_address(header, i);
    }
    v->clear_vector(v);
    free(v);
}

//Understand polymorphism
void exercice_4()
{
    printf("Vector 3D:\n");
    vector_2* v = build_vector_2(Three, (int[]){2,3,4});
    int index=0;
    for(double* i=v->get_first(v);i<=v->get_last(v);i=v->get_next(i))
    {
        (*i)=++index;
    }
    v->to_string(v);
    printf("Value at [0,1,2]:%lf\n", *v->get_element_at(v, (int[]){0,1,2}));
    v->clear_vector(v);
    free(v);
    printf("Vector 2D:\n");
    v = build_vector_2(Two, (int[]){3,3});
    index=0;
    for(double* i=v->get_first(v);i<=v->get_last(v);i=v->get_next(i))
    {
        (*i)=++index;
    }
    v->to_string(v);
    printf("Value at [1,1]:%lf\n", *v->get_element_at(v, (int[]){1,1}));
    v->clear_vector(v);
    printf("Vector 1D:\n");
    v = build_vector_2(One, (int[]){10});
    index=0;
    for(double* i=v->get_first(v);i<=v->get_last(v);i=v->get_next(i))
    {
        (*i)=++index;
    }
    v->to_string(v);
    printf("Value at [4]:%lf\n", *v->get_element_at(v, (int[]){5}));
    v->clear_vector(v);
    free(v);
}

int main()
{
   exercice_4();
}