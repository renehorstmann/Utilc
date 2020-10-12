#include <stdio.h>
#include <limits.h>

#include "utilc/dynarray.h"

// defines all functions for a float array
DynArray(float, FloatArray, float_array)

// same as DynArray, but will not raise a signal if an allocation error occurs
DynArrayTry(float, FloatArrayTry, float_array_try)

typedef struct Foo {
    int i;
    float f;
} Foo;

// defines all functions for a Foo array
DynArray(Foo, FooArray, foo_array)

// dynamic string
DynArray(char, StrArr, str_arr)

typedef int point[2];

// will not compile, a c array can't be copied, so push and pop would give an error!
//DynArray(point, PointArray, point_array)

// so we use an an dynamic array without push and pop:
DynArrayWithoutCopy(point, PointArray, point_array)

int main() {

    // creation of a DynArray on the stack
    FloatArray array = {0};
    // or:  FloatArray array = DYN_ARRAY_INIT;

    // copy elements into the end of the DynArray
    for(int i=0; i<10; i++)
        float_array_push(&array, (float) i);

    // creates items in the end of the array and returns its pointers
    for(int i=0; i<5; i++) {
        float *added = float_array_append(&array);
        *added = (float)(i*i+100);
    }

    printf("cap: %d\n", array.capacity);
    while(array.size)
        printf("%f\n", float_array_pop(&array));


    // DynArray on the heap
    FooArray *foos = (FooArray*) calloc(1, sizeof(FooArray));
    for(int i=0; i<10; i++)
        foo_array_push(foos, (Foo){i, 1.5f*(float)i});

    printf("cap: %d\n", foos->capacity);
    while(foos->size) {
        Foo f = foo_array_pop(foos);
        printf("%i %f\n", f.i, f.f);
    }

    // dynamic string allocation:
    StrArr str = {0};
    str_arr_push(&str, 'H');
    str_arr_push(&str, 'e');
    str_arr_push(&str, 'l');
    str_arr_push(&str, 'l');
    str_arr_push(&str, 'o');
    char *c = str_arr_append(&str);
    *c = ' ';
    str_arr_push_array(&str, "World", 6);    // World + '\0'

    printf("%s\n", str.array);
    //...
    str_arr_kill(&str);

    PointArray points = {0};
    point *p = point_array_append(&points);
    (*p)[0] = 20;
    (*p)[1] = 21;
    int *pi = *point_array_append(&points);
    pi[0] = 30;
    pi[1] = 31;

    for(int i=0; i<points.size; i++)
        printf("%d + %d\n", points.array[i][0], points.array[i][1]);


    FloatArrayTry error_try = {0};
    float_array_try_resize(&error_try, INT_MAX);
    printf("%p", (void*) error_try.array);

    // should crash with a signal (DYN_ARRAY_SIGNAL = SIGABRT)
    // FloatArray error = {0};
    // float_array_resize(&error, INT_MAX);
}
