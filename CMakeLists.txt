cmake_minimum_required(VERSION 3.12)

project(ispc_mark LANGUAGES CXX)

find_package(benchmark CONFIG REQUIRED)

include(extern/cmake-helpers/cmake-helpers.cmake)

add_ispc_object_library(benchmark-ispc-obj ${CMAKE_SOURCE_DIR}/src/src.ispc
    TARGETS 
        sse2-x2
        sse4-x2
        avx1-x2
        avx1.1-x2
        avx2-x2
    64BIT_ADDRESSING 
    PIC
    HEADER_PATH ispc/
)
add_executable(benchmark-ispc ${CMAKE_SOURCE_DIR}/src/benchmark.cpp)
target_link_libraries(benchmark-ispc PRIVATE benchmark-ispc-obj benchmark::benchmark benchmark::benchmark_main)

add_executable(benchmark ${CMAKE_SOURCE_DIR}/src/benchmark.cpp ${CMAKE_SOURCE_DIR}/src/src.cpp)
target_include_directories(benchmark PRIVATE ${CMAKE_BINARY_DIR}/ispc/include)
target_link_libraries(benchmark PRIVATE benchmark::benchmark benchmark::benchmark_main)
