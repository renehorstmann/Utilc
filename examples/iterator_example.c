#include <stdio.h>

#include "utilc/iterator.h"


void print_it(const int *index, intiterator it) {
    // iterator is valid, until the returned pointer != end
    // it.next(&it) returns the pointer to the next value
    for(;index != it.end; index = it.next(&it)) {
        int i = *index;
        printf("%d ", i);
    }
    puts("");
}

int main() {
    // interface object
    intiterator it;

    // contructor and start for a range counting to (exc.) 10
    const int *index = intiterator_range_begin(&it, 10);
    print_it(index, it);
    // 0 1 2 3 4 5 6 7 8 9

    index = intiterator_full_range_begin(&it, 20, 0, -3);
    print_it(index, it);
    // 20 17 14 11 8 5 2

    int indices[5] = {99, -2, 30, 5, 6};
    index = intiterator_indices_begin(&it, indices, 5);
    print_it(index, it);
    // 99 -2 30 5 6
}
