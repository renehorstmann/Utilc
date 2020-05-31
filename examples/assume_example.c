#include <stdbool.h>

//#define NDEBUG
#include "utilc/assume.h"

int main() {
    assume(true, "like assert, nothing happens");

    int sum = 5 + 5;
    assume(sum == 11, "math should fail, sum is: %d", sum);
    // will print an error message and raise SIGABRT


    // with NDEBUG defined:
    // An assumption in the program failed: math should fail, sum is: 10

    // without:
    // Assumption failed: sum == 11 at .../Utilc/examples/assume_example.c:10 math should fail, sum is: 10
}

