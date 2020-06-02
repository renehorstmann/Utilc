#include <stdio.h>

#include "utilc/strpool.h"

int main() {

    char buf[128];
    strcat_into(buf, "A", "B", "C", "DEF");
    puts(buf);

    puts(sp_reverse(buf));
    puts(sp_iter(buf, 1, 5, 2));
    puts(sp_iter(buf, 1, 5000, -2));
    puts(sp_iter(buf, -4, -1, 1));

    puts(sp_replace("He11o Wor1d", "1", "l"));
    puts(sp_replace("He11o Wor1d", " ", ""));
    puts(sp_replace("He11o Wor1d", " ", " Foo "));

    char *c = sp_cat("Hello", " ", "World");

    // removes c from the string pool, so that it will not be freed
    sp_get_ownership(c);

    // will free all created strings from sp_* except of c
    sp_free();

    // will print:
    // ABCDEF
    // FEDCBA
    // BD
    // FDB
    // CDE
    // Hello World
    // He11oWor1d
    // He11o Foo Wor1d
}
