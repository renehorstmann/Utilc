#include <stdio.h>

#include "utilc/strviu.h"


int main() {

    // hello world
    const char *cstring = " \t  Hallo Welt  \t\n  ";
    strviu viu = ToStrViu(cstring);
    printf("start: ");
    sv_print(viu);

    viu = sv_strip(viu, ' ');   //stripping whitespace uses isspace internally
    printf("strip: ");
    sv_print(viu);

    strviuarray splits = sv_split(viu, ' ');
    for(int i=0; i<splits.size; i++) {
        printf("split[%d]: ", i);
        sv_print(splits.array[i]);
    }

    // determine function parameters:
    viu = ToStrViu("int foo(const char *src  , char *dst\n, int n);");
    viu = sv_eat_until(viu, '(');
    viu.begin++;

    int end_pos = sv_find_first(viu, ')');
    viu.end = viu.begin+end_pos;

    printf("paremeters: <%s>\n", sv_heap_cpy(viu));
    splits = sv_split(viu, ',');
    for(int i=0; i<splits.size; i++) {
        printf("parameter[%d] ", i);
        sv_print(sv_strip(splits.array[i], ' '));
    }


    viu = ToStrViu("const int ** const ** pttr_fun");
    int ptr_cnt = sv_count(viu, '*');
    printf("ptr_fun has %d *\n", ptr_cnt);




    // program will print:
    //start: (strviu) { 	  Hallo Welt
    //  }
    //strip: (strviu) {Hallo Welt}
    //split[0]: (strviu) {Hallo}
    //split[1]: (strviu) {Welt}
    //paremeters: <const char *src  , char *dst
    //, int n>
    //parameter[0] (strviu) {const char *src}
    //parameter[1] (strviu) {char *dst}
    //parameter[2] (strviu) {int n}
    //ptr_fun has 4 *
}
