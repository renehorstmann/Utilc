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
}
