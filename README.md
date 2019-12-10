# Utilc
Some independent single header file libraries for C(++) programming.

## Getting Started
Copy a header file for its library to your project and have fun.
The libraries are written in C and compatible with C++ (tested on GCC 7.4.0)

### Libraries
* [StrViu](#S-StrViu): string view and functions for it
* [DynArray](#S-DynArray): creates a dynamic array of a given type
* [HashMap](#S-HashMap): creates a hashmap for a given key and value type
* [Iterator](#S-Iterator): interface for iterating over ranges or indices
* [Alloc](#S-Alloc): create space on the heap with error check


## <a name="S-StrViu"></a>StrViu
[strviu.h](include/utilc/strviu.h) is a library to handle string views in C.
```c
typedef struct {
    char *begin;    // begin of the string
    char *end;      // pointer points after the last character (to the \0 for a cstring)
} strviu;
```
The example shows how to easily use it for parsing strings.
```c
#include "strviu.h"
//...
int main() {
    // determine function parameters:
    strviu viu = ToStrViu("int foo(const char *src  , char *dst\n, int n);");
    viu = sv_eat_until(viu, '(');                       // sets the start of the view to the next '('
    viu.begin++;                                        // set the start after the '('
    
    int end_pos = sv_find_first(viu, ')');              // returns the first index of ')'
    viu.end = viu.begin+end_pos;                        // set the end to the ')'
    
    printf("paremeters: <%s>\n", sv_heap_cpy(viu));
    strviuarray splits = sv_split(viu, ',');            // returns an array of views, seperated by ','
    for(int i=0; i<splits.size; i++) {
        strviu param = sv_strip(splits.array[i], ' ');  // removes leading and ending ' ' (+ \t,\n)
        printf("parameter[%d] <%s>\n", i, sv_heap_cpy(param));
    }

    // output:
    //paremeters: <const char *src  , char *dst
    //, int n>
    //parameter[0] <const char *src>
    //parameter[1] <char *dst>
    //parameter[2] <int n)>
}
```

## <a name="S-DynArray"></a>DynArray
The library header file [dynarray.h](include/utilc/dynarray.h) defines macros to create dynamic arrays.
These arrays preallocate memory for faster resizing.
(like a std::vector)
```c
#include "dynarray.h"
//...

// define the functions for a dynamic string array
DynArray(char, StrArr)

int main() {
    StrArr str = {};                // creates a string array
    StrArr_push(&str, 'H');         // copys a char into the end
    StrArr_push(&str, 'e');
    StrArr_push(&str, 'l');
    StrArr_push(&str, 'l');
    StrArr_push(&str, 'o');

    // appends a char into the end and returns its pointer    
    char *c = StrArr_append(&str);  
    *c = ' ';
    
    // copies an array of chars into the string array (6 chars: World + '\0')
    StrArr_push_array(&str, "World", 6);
    printf("%s", str.array);
    //...

    // frees the array
    StrArr_kill(&str);
}
```

## <a name="S-HashMap"></a>HashMap
In the header file [hashmap.h](include/utilc/hashmap.h) are macros to create hash maps.
The macro HashMap takes besides the name, the types for key and value.
And the four functions: hash from key, key compare, key copy and key kill.
The macro StrHashMap is a sub macro, in which the key is pre defined as const char *, 
so only the name and value type are needed.
```c
#include "hashmap.h"
//...

// define a hash map with a string as key and an int as value
StrHashMap(IntMap, int)

int main() {

    IntMap map;
    IntMap_new(&map, 10);
    
    // get and add entry, if not available in the map
    *IntMap_get(&map, "test") = 1;
    *IntMap_get(&map, "Hello World") = 3;
    int *val = IntMap_get(&map, "test");
    *val = -1;

    //...

    // removing the map entry "Hello World"
    IntMap_remove(&map, "Hello World");

    //...

    IntMap_kill(&map);
}
```

## <a name="S-Iterator"></a>Iterator
The interface intiterator is in the header file [iterator.h](include/utilc/iterator.h).
This interface can be used to iterate over both, a range (e. g. 0:10, 20:10:-1) or an indices array.
```c
#include "iterator.h"
//...

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
```

## <a name="S-Alloc"></a>Alloc
The file [alloc.h](include/utilc/alloc.h) includes some functions and macros to create space on the heap.
If the malloc (calloc, realloc) fails, an assertion is thrown.
```c
#include "alloc.h"
//...

int main() {
    // allocates 10 ints with a checked malloc
    int *data = New(int, 10);

    // the 20 ints will be 0 (checked calloc)
    int *data2 = New0(int, 20);

    // checked realloc
    data = ReNew(int, data, 30);

    // frees data and sets its pointer to NULL
    Free0(data);
    assert(data==NULL);

    // unchecked malloc
    char *str = TryNew(char, 1000);
}
```


## Running the examples
The top directory of this project contains a CmakeLists.txt file, which sets up the examples for each library

## Author

* **René Horstmann**

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details
