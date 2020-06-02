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
}
