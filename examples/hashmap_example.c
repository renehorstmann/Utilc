#include <stdio.h>

#include "utilc/hashmap.h"


// value_type, class_name, method prefix name
// key_type is a string (const char *)
StrHashMap(int, IntMap, int_map)


typedef struct Object{
    int i;
    float f;
    // ...
} Object;

typedef struct Value {
    const char *val;
    int i;
    // ...
} Value;

static unsigned object_map_impl_hash(Object key) {
    unsigned hash = 5381;
    hash *= key.i;
    hash += (unsigned) (12345678 * key.f);
    return hash;
}
static bool object_map_impl_keycmp(Object a, Object b) {
    return a.i == b.i && a.f == b.f;
}
static Object object_map_impl_keycpy(Object cpy) {
    return cpy;
}
static void object_map_impl_keykill(Object key) {
    // pass
}

// custom hash map:
// key_type = Object, value_type = Value
// class_name = ObjectMap, method prefix name = object_map
// functions to work on...
HashMap(Object, Value,
        ObjectMap, object_map,
        object_map_impl_hash, object_map_impl_keycmp, object_map_impl_keycpy, object_map_impl_keykill)


void printintmap_manual(IntMap map) {
    for(int i=0; i<map.map_size; i++) {
        printf("hash: %d\n", i);
        IntMap_Item *item = map.map[i];
        while(item) {
            printf("item: key<%s> val<%d>\n",item->key, item->value);
            item = item->next;
        }
    }
}

void printintmap_iterator(IntMap map) {
    IntMap_Iter it = int_map_get_iter(&map);
    IntMap_Item *item;
    while((item = int_map_Iter_next(&it)) != NULL) {
        printf("item: key<%s> val<%d>\n", item->key, item->value);
    }
}

int main() {

    IntMap map;
    int_map_new(&map, 10);
    *int_map_get(&map, "test") = 1;
    *int_map_get(&map, "testi") = 2;
    *int_map_get(&map, "Hello World") = 3;
    *int_map_get(&map, "") = 4;
    *int_map_get(&map, "Gustavson") = 5;
    int *val = int_map_get(&map, "test");
    *val = -1;

    puts("manual:");
    printintmap_manual(map);

    int_map_remove(&map, "");

    puts("\niterator");
    printintmap_iterator(map);

    int_map_kill(&map);
    puts("\n killed...");
    printintmap_iterator(map);

    // custom map
    ObjectMap om;
    object_map_new(&om, 1000);
    Value *o = object_map_get(&om, (Object){10, 20.0f});
    o->i = 100;
    o->val = "Hello World";

    o = object_map_get(&om, (Object){11, 21.0f});
    o->i = 101;
    o->val = "Hello Worldy";

    o = object_map_get(&om, (Object){10, 20.0f});
    printf("object: %d %s\n", o->i, o->val);

    object_map_kill(&om);

}
