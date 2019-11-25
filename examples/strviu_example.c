#include <stdio.h>

#include "utilc/strviu.h"


int main() {

    // hello world
    const char *cstring = " \t  Hallo Welt  \t\n  ";
    strviu viu = ToStrViu(cstring);
    printf("start: <%s>\n", sv_heap_cpy(viu));

    viu = sv_strip(viu, ' ');   //stripping whitespace uses isspace internally
    printf("strip: <%s>\n", sv_heap_cpy(viu));

    strviuarray splits = sv_split(viu, ' ');
    for(size_t i=0; i<splits.size; i++) {
        printf("split[%zu]: <%s>\n", i, sv_heap_cpy(splits.array[i]));
    }

    // determine function parameters:
    viu = ToStrViu("int foo(const char *src  , char *dst\n, int n);");
    viu = sv_eat_until(viu, '(');
    viu.begin++;

    int end_pos = sv_find_first(viu, ')');
    viu.end = viu.begin+end_pos;

    printf("paremeters: <%s>\n", sv_heap_cpy(viu));
    splits = sv_split(viu, ',');
    for(size_t i=0; i<splits.size; i++) {
        printf("parameter[%zu] <%s>\n", i, sv_heap_cpy(sv_strip(splits.array[i], ' ')));
    }


    viu = ToStrViu("const int ** const ** pttr_fun");
    int ptr_cnt = sv_count(viu, '*');
    printf("ptr_fun has %d *\n", ptr_cnt);


    viu = ToStrViu("12345 12.34");
    int32_t parsed_int32;
    viu = sv_eat_int32_ascii(viu, &parsed_int32);
    float parsed_float;
    viu = sv_eat_float_ascii(viu, &parsed_float);
    printf("parsed is %d and %f, remaining viu len is %zu\n", parsed_int32, parsed_float, sv_length(viu));

    double binary_test = 456.789;
    viu = (strviu) {(char *) &binary_test, (char *) &binary_test+8};
    double parsed_double;
    if(sv__helper_system_is_binary_little_endian_())
        viu = sv_eat_double_binary_le(viu, &parsed_double);
    else
        viu = sv_eat_double_binary_be(viu, &parsed_double);
    printf("parsed binary is %f, remaining viu len is %zu\n", parsed_double, sv_length(viu));

    // sv_eat_int returns {NULL, "error message"} if an error occurs (here only 3 ints /5 are in the viu)
    viu = ToStrViu("1 2 3");
    int parsed_array[5];
    for(int i=0; i<5; i++)
        viu = sv_eat_int32_ascii(viu, &parsed_array[i]);
    printf("viu begin: %s viu end: %s", viu.begin, viu.end);



    // program will print:
    //start: < 	  Hallo Welt
    //  >
    //strip: <Hallo Welt>
    //split[0]: <Hallo>
    //split[1]: <Welt>
    //paremeters: <const char *src  , char *dst
    //, int n>
    //parameter[0] <const char *src>
    //parameter[1] <char *dst>
    //parameter[2] <int n)>
    //ptr_fun has 4 *
    //parsed is 12345 and 12.340000, remaining viu len is 0
    //parsed binary is 456.789000, remaining viu len is 0
    //viu begin: (null) viu end: sv_eat_int32_ascii failed
}
