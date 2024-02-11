#include <stdio.h>
#include <stdlib.h>

void memory_lost_reachable()
{
    char * mem = malloc(100);
    exit(0);
}


void memory_def_lost()
{
    int * mem = malloc(100);
    int tmp = 1;
    mem = &tmp;
    exit(0);
}

void memory_indirect_lost()
{
    int * a = malloc(sizeof(int));
    int ** array_of_int = malloc(sizeof(int *));
    *a = 5;
    array_of_int[0] = a;
    a = malloc(sizeof(int));
    array_of_int = malloc(sizeof(int*));
    //printf("size of int is %lu\n", sizeof(int));
    exit(0);
}

int* possibly_lost()
{
    int * a = malloc(100);
    a = a + 1;
    exit(0);
}

 int* uninitialised_stack_helper()
{
    int *a;
    int b = 10;
    a = &b;
    return a;
}

void uninitialised_stack()
{
    int * ret = invalid_read_helper();
    printf("ret is %d\n", *ret);
}

void uninitialized_heap()
{
    char* array = malloc(10);
    printf("char val at 0 is %c\n", array[0]);
}

int main()
{
    memory_lost_reachable();
   // memory_def_lost();
    //memory_indirect_lost();
   // possibly_lost();
   //uninitialized_heap();
   uninitialised_stack();


}