cmake_minimum_required(VERSION 2.6)
project(MINI_ROHC)
set(CMAKE_CFLAGS "${CMAKE_CFLAGS} -g -Wall -O0 ")
include_directories(./include)

set( rohc_srcs
    ./src/rohc.c
    ./src/c_ip.c
    ./src/c_util.c
    ./src/comp.c
    ./src/d_ip.c
    ./src/d_util.c
    ./src/decomp.c
    ./src/feedback.c
    ./src/proc_rohc.c
)

set (rohc_test
    ./test/testapp.c
)

add_library(mini_rohc STATIC ${rohc_srcs})
add_executable(rohc_test ${rohc_test})
target_link_libraries(rohc_test mini_rohc)