cmake_minimum_required(VERSION 4.1)
project(simulare_model)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)


find_package(Qt6 COMPONENTS
        Core
        Gui
        Widgets
        REQUIRED)

add_executable(simulare_model main.cpp
    gui.cpp
    instrument.h
    repo.cpp
    service.cpp
    tests.cpp)
target_link_libraries(simulare_model
        Qt::Core
        Qt::Gui
        Qt::Widgets
)

