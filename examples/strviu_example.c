#include <stdio.h>

#include "utilc/strviu.h"


int main() {

    // hello world
    const char *cstring = " \t  Hallo Welt  \t\n  ";
    StrViu viu = ToStrViu(cstring);
    printf("start: <%s>\n", sv_heap_cpy(viu));

    viu = sv_strip(viu, ' ');   //stripping whitespace uses isspace internally
    printf("strip: <%s>\n", sv_heap_cpy(viu));

    StrViuArray splits = sv_split(viu, ' ');
    for(int i=0; i<splits.size; i++) {
        printf("split[%d]: <%s>\n", i, sv_heap_cpy(splits.array[i]));
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
        printf("parameter[%d] <%s>\n", i, sv_heap_cpy(sv_strip(splits.array[i], ' ')));
    }


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
}
