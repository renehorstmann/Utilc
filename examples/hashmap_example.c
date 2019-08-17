#include <stdio.h>

#include "utilc/hashmap.h"


StrHashMap(IntMap, int)

typedef struct {
    int i;
    float f;
} Object;

typedef struct {
    const char *val;
    int i;
} Value;

static unsigned ObjectMap_impl_hash(Object key) {
    unsigned hash = 5381;
    hash *= key.i;
    hash += (unsigned) (12345678 * key.f);
    return hash;
}
static bool ObjectMap_impl_keycmp(Object a, Object b) {
    return a.i == b.i && a.f == b.f;
}
static Object ObjectMap_impl_keycpy(Object cpy) {
    return cpy;
}
static void ObjectMap_impl_keykill(Object key) {
    // pass
}

HashMap(ObjectMap, Object, Value, ObjectMap_impl_hash, ObjectMap_impl_keycmp, ObjectMap_impl_keycpy, ObjectMap_impl_keykill)


void printintmap(IntMap map) {
    puts("\nintmap:");
    for(int i=0; i<map.map_size; i++) {
        printf("hash: %d\n", i);
        struct IntMap_Item_ *item = map.map[i];
        while(item) {
            printf("item: key<%s> val<%d>\n",item->key, item->value);
            item = item->next;
        }
    }
}
int main() {

    IntMap map;
    IntMap_new(&map, 10);
    *IntMap_get(&map, "test") = 1;
    *IntMap_get(&map, "testi") = 2;
    *IntMap_get(&map, "Hello World") = 3;
    *IntMap_get(&map, "") = 4;
    *IntMap_get(&map, "Gustavson") = 5;
    int *val = IntMap_get(&map, "test");
    *val = -1;

    printintmap(map);

    IntMap_remove(&map, "");
    printintmap(map);

    IntMap_kill(&map);
    printintmap(map);

    ObjectMap om;
    ObjectMap_new(&om, 1000);
    Value *o = ObjectMap_get(&om, (Object){10, 20.0f});
    o->i = 100;
    o->val = "Hello World";

    o = ObjectMap_get(&om, (Object){11, 21.0f});
    o->i = 101;
    o->val = "Hello Worldy";

    o = ObjectMap_get(&om, (Object){10, 20.0f});
    printf("object: %d %s\n", o->i, o->val);

    ObjectMap_kill(&om);

}