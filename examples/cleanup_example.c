#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "utilc/cleanup.h"


static void print_on_clean_up(int *i) {
    printf("freeing: %d\n", *i);
    free(i);
}

static void simple() {
    // create the CleanUp member
    CleanUp clean = {0};
    // or: CleanUp clean = CleanUp_INIT;

    // data on heap that must be freed at the end of the function
    int *heap = (int *) malloc(sizeof(int));
    CleanUpAdd(&clean, heap, print_on_clean_up);

    // set data
    *heap = 101;

    // CleanUp will call print_on_clean_up(heap) to free the data
    CleanUpClean(&clean);
}


static void multi_returns(bool way_one) {
    CleanUp clean = CleanUp_INIT;

    int *heap = (int *) malloc(sizeof(int));

    // direct call to the function instead of the macro CleanUpAdd
    CleanUp_add(&clean, (void *) heap, (CLEAN_UP_FUNCTION_TYPE) print_on_clean_up);

    *heap = -43;

    if (way_one) {
        CleanUpClean(&clean);
        return;
    }

    const char *msg_on_cleanup = "Hello CleanUp";

    // will call puts(msg_on_cleanup) on clean
    CleanUpAdd(&clean, msg_on_cleanup, puts);

    // direct cal to the function instead of the macro CleanUpClean
    CleanUp_clean(&clean);
}

#ifdef __GNUC__

static void auto_clean(bool way_one) {
    CleanUpAutoClean clean = {0};
    // CleanUp_clean(&clean) will be called automatically on function exit

    CleanUpAdd(&clean, "Hello AutoClean", puts);

    if (way_one) {
        CleanUpAdd(&clean, "way one", puts);
        return;
    }

    CleanUpAdd(&clean, "way two", puts);
}

#endif

typedef struct Vector {
    float *data;
    int size;
} Vector;

static void Vector_init(Vector *self, int size) {
    self->data = (float *) malloc(sizeof(float) * size);
    self->size = self->data ? size : 0;
}

static void Vector_print(const Vector *self) {
    printf("Vector: ");
    if(self->size == 0 ) {
        puts("empty");
    } else {
        for (int i = 0; i < self->size; i++)
            printf("%.1f ", self->data[i]);
        puts("");
    }
}

static void Vector_kill(Vector *self) {
    Vector_print(self);
    free(self->data);
    self->data = NULL;
    self->size = 0;
}

static void structs() {
    CleanUp clean = {0};

    Vector vec;
    Vector_init(&vec, 6);
    CleanUpAdd(&clean, &vec, Vector_kill);

    for (int i = 0; i < 6; i++)
        vec.data[i] = (float) (i * i);

    Vector vec2;
    Vector_init(&vec2, 1);
    CleanUpAdd(&clean, &vec2, Vector_kill);

    vec2.data[0] = 123.4f;

    // move data
    float *moved = vec2.data;
    vec2.data = NULL;
    vec2.size = 0;
    CleanUpAdd(&clean, moved, free);

    printf("moved first float: %.1f\n", *moved);

    CleanUpClean(&clean);
}

static void scope() {
    // Macro to create a CleanUp with the name clean_up_scobe_member__
    CleanUpScopeInit;
    // also available: CleanUpScopeAutoCleanInit;

    // add an item to clean_up_scobe_member__
    CleanUpScopeAdd("hello scope", puts);

    // clean clean_up_scobe_member__
    CleanUpScopeClean;
}

static void free_ptr(void **ptr) {
    printf("freeing ptr: %p\n", *ptr);
    free(*ptr);
}

static void dynamic_ptr() {
    CleanUpScopeInit;
    char *array = (char *) malloc(10);

    // addind a pointer to array, instead of array itself,
    // so if array points to another mem location, CleanUp will clean the new one.
    CleanUpScopeAdd(&array, free_ptr);

    printf("ptr: %p\n", (void *) array);

    // reassign to a new memory location...
    array = (char*) realloc(array, 1000000);

    printf("ptr: %p\n", (void *) array);

    CleanUpScopeClean;
}

int main() {

    simple();
    // will print:
    //freeing: 101

    multi_returns(true);
    // will print:
    //freeing: 43

    multi_returns(false);
    // will print:
    //freeing: 43
    //Hello CleanUp

#ifdef __GNUC__
    auto_clean(true);
    // will print:
    //Hello AutoClean
    //way one

    auto_clean(false);
    // will print:
    //Hello AutoClean
    //way two
#endif

    structs();
    // will print:
    //moved first float: 123.4
    //Vector: 0.0 1.0 4.0 9.0 16.0 25.0
    //Vector: empty

    scope();
    // will print:
    //hello scope

    dynamic_ptr();
    // can print something like:
    //ptr: 0x5560c5d38690
    //ptr: 0x7fc4972f9010
    //freeing ptr: 0x7fc4972f9010
}
