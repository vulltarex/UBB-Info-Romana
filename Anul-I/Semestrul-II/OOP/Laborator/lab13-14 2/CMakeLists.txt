cmake_minimum_required(VERSION 4.1)
project(lab13_14_2)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)


find_package(Qt6 COMPONENTS
        Core
        Gui
        Widgets
        REQUIRED)

add_executable(lab13_14_2 main.cpp
        activitate.cpp
        gui.cpp
lista_activitati.cpp
main.cpp
raport.cpp
repository.cpp
service.cpp
tests.cpp
ui.cpp
validator.cpp
)
target_link_libraries(lab13_14_2
        Qt::Core
        Qt::Gui
        Qt::Widgets
)

