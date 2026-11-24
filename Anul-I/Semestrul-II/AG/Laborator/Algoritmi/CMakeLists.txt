cmake_minimum_required(VERSION 4.1)
project(Algoritmi)

set(CMAKE_CXX_STANDARD 20)

add_executable(Algoritmi
        main.cpp
        huffman_cod.cpp
        huffman_decod.cpp
        max_flow_ek.cpp
        max_flow_pr.cpp
        mst_prim.cpp
        prufer_cod.cpp
        prufer_decod.cpp
)
