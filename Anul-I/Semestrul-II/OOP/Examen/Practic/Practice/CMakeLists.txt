cmake_minimum_required(VERSION 4.1)
project(Practice)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(CMAKE_PREFIX_PATH "/Users/cristianfilip/Qt/6.11.1/macos")

find_package(Qt6 COMPONENTS
        Core
        Gui
        Widgets
        REQUIRED)

add_executable(Practice main.cpp
        masina.h
        repo.cpp
        repo.h
        service.cpp
        service.h
        gui.cpp
        gui.h
        model.h)
target_link_libraries(Practice
        Qt::Core
        Qt::Gui
        Qt::Widgets
)

