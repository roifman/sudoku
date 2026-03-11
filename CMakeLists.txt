cmake_minimum_required(VERSION 3.20)
project(sudoku LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)


find_package(Qt6 COMPONENTS Quick REQUIRED)

add_library(sudoku_core
    src/board.cpp
    src/filepuzzlesource.cpp
)
target_include_directories(sudoku_core PUBLIC include)

qt_add_executable(sudoku_qml
    src/main_qml.cpp
    src/sudokucontroller.cpp
    include/sudokucontroller.h
)
target_include_directories(sudoku_qml PUBLIC include)
target_link_libraries(sudoku_qml PRIVATE sudoku_core Qt6::Quick)

qt_add_qml_module(sudoku_qml
    URI SudokuUI
    VERSION 1.0
    QML_FILES qml/Main.qml
)
