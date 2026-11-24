cmake_minimum_required(VERSION 4.1)
project(Lab2_4 C)

set(CMAKE_C_STANDARD 11)

add_executable(Lab2_4 main.c
        domain.c
        repo.c
        service.c
        tests.c
        ui.c
        validator.c
)


target_compile_options(Lab2_4 PRIVATE --coverage)
target_link_options(Lab2_4 PRIVATE --coverage)