cmake_minimum_required(VERSION 4.1)
project(PracticOOP)

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

add_executable(PracticOOP main.cpp
        student.h
        repo.cpp
        repo.h
        service.h
        GUI.cpp
        GUI.h
        table_model.h
        tests.h)
target_link_libraries(PracticOOP
        Qt::Core
        Qt::Gui
        Qt::Widgets
)

