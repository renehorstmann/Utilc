#include <stdio.h>

#include "utilc/dynarray.h"

// defines all functions for a float array
DynArray(float, FloatArray)

typedef struct Foo {
    int i;
    float f;
} Foo;

// defines all functions for a Foo array
DynArray(Foo, FooArray)

// dynamic string
DynArray(char, StrArr)

typedef int point[2];
// dynamic int[2] (a c array can't be copied, so push and pop would give an error)
DynArrayWithoutCopy(point, PointArray)

int main() {

    // creation of a DynArray on the stack
    FloatArray array = {0};
    // or:  FloatArray array = DynArray_INIT;

    // copy elements into the end of the DynArray
    for(int i=0; i<10; i++)
        FloatArray_push(&array, (float) i);

    // creates items in the end of the array and returns its pointers
    for(int i=0; i<5; i++) {
        float *added = FloatArray_append(&array);
        *added = (float)(i*i+100);
    }

    printf("cap: %zu\n", array.capacity);
    while(array.size)
        printf("%f\n", FloatArray_pop(&array));


    // DynArray on the heap
    FooArray *foos = (FooArray*) calloc(1, sizeof(FooArray));
    for(int i=0; i<10; i++)
        FooArray_push(foos, (Foo){i, 1.5f*(float)i});

    printf("cap: %zu\n", foos->capacity);
    while(foos->size) {
        Foo f = FooArray_pop(foos);
        printf("%i %f\n", f.i, f.f);
    }

    // dynamic string allocation:
    StrArr str = {0};
    StrArr_push(&str, 'H');
    StrArr_push(&str, 'e');
    StrArr_push(&str, 'l');
    StrArr_push(&str, 'l');
    StrArr_push(&str, 'o');
    char *c = StrArr_append(&str);
    *c = ' ';
    StrArr_push_array(&str, "World", 6);    // World + '\0'

    printf("%s\n", str.array);
    //...
    StrArr_kill(&str);

    PointArray points = {0};
    point *p = PointArray_append(&points);
    (*p)[0] = 20;
    (*p)[1] = 21;
    int *pi = *PointArray_append(&points);
    pi[0] = 30;
    pi[1] = 31;

    for(size_t i=0; i<points.size; i++)
        printf("%d + %d\n", points.array[i][0], points.array[i][1]);
}
