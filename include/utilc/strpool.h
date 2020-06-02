#ifndef UTILC_STRPOOL_H
#define UTILC_STRPOOL_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <signal.h>
#include <assert.h>
#include <math.h>


#define SP_THREAD_LOCAL __thread
#define SP_CAPACITY_STEPS 8


//
// None pool functions
//

/**
 * Concatenates multiple strings into dst
 * @param dst: buffer that will be filled with the concatenated strings
 * @param strings: A list of strings, that ends with NULL
 * @return: dst
 */
static char *strcat_into_v(char *dst, char **strings) {
    if(*strings)
        strcpy(dst, *strings++);
    while(*strings)
        strcat(dst, *strings++);
    return dst;
}
/** Concatenates all strings behind dst into dst */
#define strcat_into(dst, ...) strcat_into_v((dst), (char*[]) {__VA_ARGS__, NULL})

/**
 * Pool member that stores all created strings in a dynamic list.
 * if used, set malloc and free.
 */
struct sp_pool {
    char **data;
    size_t data_size;
    size_t data_capacity;
    void *(*malloc)(size_t size);
    void (*free)(void *data);
};

/** Default pool member for each file and thread (always uses stdlib malloc and free) */
static SP_THREAD_LOCAL struct sp_pool sp_pool_member_;

/** If set, another pool instead the one above will be used */
static struct sp_pool *sp_pool_used;

/** Appends an string to the pool, so that sp_free will free it */
static void sp_pool_append(char *str) {
    struct sp_pool *pool = sp_pool_used ? sp_pool_used : &sp_pool_member_;
    if(++pool->data_size > pool->data_capacity) {
        pool->data_capacity += SP_CAPACITY_STEPS;
        pool->data = (char **) realloc(pool->data, pool->data_capacity * sizeof(char *));
    }
    if(!pool->data) {
        fprintf(stderr, "sp_pool_append failed, alloc error\n");
        raise(SIGABRT);
    }
    pool->data[pool->data_size-1] = str;
}

/** Frees all strings in the pool */
static void sp_free() {
    void (*vfree)(void *) = sp_pool_used ? sp_pool_used->free : free;
    struct sp_pool *pool = sp_pool_used ? sp_pool_used : &sp_pool_member_;
    for(int i=0; i<pool->data_size; i++)
        vfree(pool->data[i]);
    free(pool->data);
    pool->data = NULL;
    pool->data_size = 0;
}

/** Allocates an string and appends it to the pool */
static char *sp_malloc(size_t size) {
    char *res = (char *) (sp_pool_used ? sp_pool_used->malloc(size) : malloc(size));
    if(!res) {
        fprintf(stderr, "sp_malloc(%zu) failed in file %s\n", size, __FILE__);
        raise(SIGABRT);
    }
    sp_pool_append(res);
    return res;
}

/**
 * Removes a string from the pool, without freeing it.
 * @param str: the string to search in the pool
 * @return: The given string if found and removed, NULL if not found.
 */
static char *sp_get_ownership(char *str) {
    struct sp_pool *pool = sp_pool_used ? sp_pool_used : &sp_pool_member_;
    for(int i=0; i<pool->data_size; i++) {
        if(pool->data[i] == str) {
            pool->data[i] = NULL;
            return str;
        }
    }
    return NULL;
}

/** Clones a string */
static char *sp_clone(char *src) {
    char *res = sp_malloc(strlen(src));
    strcpy(res, src);
    return res;
}

/** Clones a string, if length > strlen(src), length+1 bytes will be allocated */
static char *sp_clone_n(char *src, size_t length) {
    if(strlen(src) > length)
        length = strlen(src);
    char *res = sp_malloc(length + 1);
    strcpy(res, src);
    return res;
}

/** Concatenates the strings together (strings must end with a NULL) */
static char *sp_cat_v(char **strings) {
    size_t size = 1;
    char **it = strings;
    while(*it)
        size += strlen(*it++);
    char *res = sp_malloc(size);
    strcat_into_v(res, strings);
    return res;
}

/** Concatenates all given strings together */
#define sp_cat(...) sp_cat_v((char*[]) {__VA_ARGS__, NULL})

/**
 * Concatenates all given strings together (strings must end with a NULL).
 * If srtlen(*strings) < length, length+1 bytes will be allocated
 */
static char *sp_cat_n_v(char **strings, size_t length) {
    size_t size = 0;
    char **it = strings;
    while(*it)
        size += strlen(*it++);
    if(size > length)
        length = size;
    char *res = sp_malloc(length + 1);
    strcat_into_v(res, strings);
    return res;
}

/** Concatenates all given strings together, if srtlen(*strings) < length, length+1 bytes will be allocated */
#define sp_cat_n(...) sp_cat_n_v((char*[]) {__VA_ARGS__, NULL})

/** Iterates and copies src, end can be larger than the string, also all parameters can be negativ */
static char *sp_iter(char *src, int begin, int end, int step) {
    assert(step != 0 && "sp_iter failed, step must not be 0");
    if(begin < 0)
        begin += (int) strlen(src);
    if(end <= 0)
        end += (int) strlen(src);
    assert(begin < end && "sp_iter failed");
    size_t range_len = strlen(src+begin);
    if(end-begin < range_len)
        range_len = end-begin;

    size_t size = (size_t) range_len / abs(step);
    char *res = sp_malloc(size+1);
    if(step > 0) {
        char *it = res;
        for(int i=0; i<range_len; i+=step)
            *it++ = src[begin+i];
    } else if(step < 0) {
        char *it = res;
        for(int i= (int) range_len-1; i>=0; i+=step)
            *it++ = src[begin+i];
    }
    return res;
}

/** Returns the reversed string of src (calls sp_iter(src, 0, 0, -1)) */
static char *sp_reverse(char *src) {
    return sp_iter(src, 0, 0, -1);
}


#endif //UTILC_STRPOOL_H
