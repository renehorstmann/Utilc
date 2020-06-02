cmake_minimum_required(VERSION 3.0)
project(Utilc)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 11)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wno-long-long -pedantic -Wno-unused-function -Wno-missing-braces")

include_directories(include)

add_executable(strviu examples/strviu_example.c)
add_executable(strviuparse examples/strviuparse_example.c)
add_executable(strpool examples/strpool_example.c)
add_executable(dynarray examples/dynarray_example.c)
add_executable(hashmap examples/hashmap_example.c)
add_executable(iterator examples/iterator_example.c)
add_executable(alloc examples/alloc_example.c)
add_executable(cleanup examples/cleanup_example.c)
add_executable(assume examples/assume_example.c)
