cmake_minimum_required(VERSION 4.1)
project(Tractoare)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

add_executable(Tractoare main.cpp
        tractor.h
        repository.cpp
        service.cpp
        service.h
        validator.cpp
        validator.h
        gui.cpp
        gui.h
        table_model.h
)

find_package(Qt6 COMPONENTS
        Core
        Gui
        Widgets
        REQUIRED)

target_link_libraries(Tractoare
        Qt::Core
        Qt::Gui
        Qt::Widgets
)


