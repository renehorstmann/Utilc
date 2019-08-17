cmake_minimum_required(VERSION 3.0)
project(Utilc)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 11)

add_executable(scope examples/scope_example.c)
target_include_directories(scope PUBLIC include)

add_executable(strviu examples/strviu_example.c)
target_include_directories(strviu PUBLIC include)

add_executable(dynarray examples/dynarray_example.c include/utilc/hashmap.h)
target_include_directories(dynarray PUBLIC include)

add_executable(hashmap examples/hashmap_example.c)
target_include_directories(hashmap PUBLIC include)