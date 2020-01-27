#include <stdio.h>

#include "utilc/strviuparse.h"

int main() {
    strviu viu = ToStrViu("12345 12.34");
    int32_t parsed_int32;
    viu = sv_eat_int32_ascii(viu, &parsed_int32);
    float parsed_float;
    viu = sv_eat_float_ascii(viu, &parsed_float);
    printf("parsed is %d and %f, remaining viu len is %zu\n", parsed_int32, parsed_float, sv_length(viu));

    double binary_test = 456.789;
    viu = (strviu) {(char *) &binary_test, (char *) &binary_test + 8};
    double parsed_double;
    if (sv__helper_system_is_binary_little_endian_())
        viu = sv_eat_double_binary_le(viu, &parsed_double);
    else
        viu = sv_eat_double_binary_be(viu, &parsed_double);
    printf("parsed binary is %f, remaining viu len is %zu\n", parsed_double, sv_length(viu));

    // sv_eat_int returns {NULL, "error message"} if an error occurs (here only 3 ints /5 are in the viu)
    viu = ToStrViu("1 2 3");
    int parsed_array[5];
    for (int i = 0; i < 5; i++)
        viu = sv_eat_int32_ascii(viu, &parsed_array[i]);
    printf("viu begin: %s viu end: %s", viu.begin, viu.end);


    // program will print:
    //parsed is 12345 and 12.340000, remaining viu len is 0
    //parsed binary is 456.789000, remaining viu len is 0
    //viu begin: (null) viu end: sv_eat_int32_ascii failed
}
