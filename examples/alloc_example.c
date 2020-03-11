#include "utilc/alloc.h"

int main() {

    // allocates 10 ints with a checked malloc
    int *data = New(int, 10);

    // should throw an assert:
    // data = ReNew(int, data, -1);

    Free0(data);
    assert(data == NULL);

    char *str = New0(char, 5);
    for(int c=0; c<5; c++)
        assert(str[c] == 0);


    char *str2 = New(char, 100);
    struct S {
        int a;
        float b;
    };

    // normal malloc (doesn't assert the pointer)
    struct S *mem = TryNew(struct S, 1000);


    Free0(str);
    Free0(str2);
    Free0(mem);
    return 0;
}
