cmake_minimum_required(VERSION 3.0)
project(Utilc)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 11)

set(CMAKE_C_FLAGS ${CMAKE_C_FLAGS} -march=native)  # march=native for best performance
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wno-long-long -pedantic -Wno-unused-function")

add_executable(scope examples/scope_example.c)
target_include_directories(scope PUBLIC include)

add_executable(strviu examples/strviu_example.c)
target_include_directories(strviu PUBLIC include)

add_executable(dynarray examples/dynarray_example.c include/utilc/hashmap.h)
target_include_directories(dynarray PUBLIC include)

add_executable(hashmap examples/hashmap_example.c)
target_include_directories(hashmap PUBLIC include)

add_executable(iterator examples/iterator_example.c)
target_include_directories(iterator PUBLIC include)

add_executable(vecmath examples/vecmath_example.c)
target_include_directories(vecmath PUBLIC include)
target_link_libraries(vecmath m)

add_executable(matmath examples/matmath_example.c)
target_include_directories(matmath PUBLIC include)
target_link_libraries(matmath m)
