#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>

#include "utilc/scope.h"

int *get_numbers(const char *str) {

    // creating a scope (Macro with ScopeType named _scope)
    Scope

    int *res = NULL;
    int n = 0;
    // adding a pointer to a data pointer (free(*pointer_to_data))
    ScopeAddData(&res)

    char *not_used = (char *) malloc(1000);
    if (!not_used)
        // if not_used couldn't be allocated, res will be freed
    ScopeLeaveReturn(NULL)
    ScopeAddData(&not_used)

    for (;;) {

        while (isspace(*str))
            str++;

        if (*str == 0) {
            // removes a previously added data (without pointer to data)
            ScopeRemoveData(res)

            // leaving the scope and freeing only not_used
            ScopeLeaveReturn(res)
        }

        char *end;
        int number = (int) strtol(str, &end, 10);
        if (str == end) {
            ScopeRemoveData(res)
            ScopeLeaveReturn(res)
        }
        str = end;

        while (!isspace(*str) && *str != 0)
            str++;

        int *re_res = (int *) realloc(res, ++n * sizeof(int));
        if (!re_res) ScopeLeaveReturn(NULL)
        res = re_res;
        res[n - 1] = number;
    }

}


typedef struct {
    char *str;
} String;

void String_new(String *self, const char *init) {
    self->str = (char *) malloc(strlen(init) + 1);
    strcpy(self->str, init);
    self->str[strlen(init)] = 0;
    printf("String created: <%s>\n", self->str);
}

void String_kill(String *self) {
    printf("String killed: <%s>\n", self->str);
    free(self->str);
    self->str = NULL;
}


int main() {

    int *numbers = get_numbers("12 13 14");
    printf("<%d> <%d> <%d>\n", numbers[0], numbers[1], numbers[2]);

    // example for a call to a destructor
    // also valid is fclose() for FILE* for example
    Scope
    String str = {0};
    String_new(&str, "Foo");
    ScopeAddCall(&str, &String_kill)

    ScopeLeaveReturn(0)


    // program will print:
    //<12> <13> <14>
    //String created: <Foo>
    //String killed: <Foo>
}
