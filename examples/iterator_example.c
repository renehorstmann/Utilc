#include <stdio.h>

#include "utilc/iterator.h"


void print_it(intiterator it) {
    // iterator is valid, until the returned pointer != end
    // it.next(&it) returns the pointer to the next value
    for(const int *index = it.get(&it); index != it.end; index = it.next(&it)) {
        int i = *index;
        printf("%d ", i);
    }
    puts("");
}

int main() {
    // interface object
    intiterator it;

    // contructor and start for a range counting to (exc.) 10
    intiterator_range_begin(&it, 10);
    print_it(it);
    // 0 1 2 3 4 5 6 7 8 9

    intiterator_full_range_begin(&it, 20, 0, -3);
    print_it(it);
    // 20 17 14 11 8 5 2

    int indices[5] = {99, -2, 30, 5, 6};
    intiterator_indices_begin(&it, indices, 5);
    print_it(it);
    // 99 -2 30 5 6
}
