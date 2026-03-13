cmake_minimum_required(VERSION 3.16)
project(sudoku_qml LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 6.5 COMPONENTS Quick Qml Core REQUIRED)

#object library
add_library(sudoku_objects OBJECT
    src/board.cpp
    src/sudokucontroller.cpp
    src/filepuzzlesource.cpp
)

set_target_properties(sudoku_objects PROPERTIES AUTOMOC ON)

target_include_directories(sudoku_objects PUBLIC include)

target_sources(sudoku_objects PUBLIC
    include/board.h
    include/sudokucontroller.h
    include/filepuzzlesource.h
    include/ipuzzlesource.h
    include/solver.h
)

target_link_libraries(sudoku_objects PUBLIC Qt6::Core Qt6::Qml Qt6::Quick)

#main executable
add_executable(sudoku_qml
    src/main_qml.cpp
    $<TARGET_OBJECTS:sudoku_objects>
)

target_include_directories(sudoku_qml PRIVATE include)

target_link_libraries(sudoku_qml PRIVATE Qt6::Quick Qt6::Qml Qt6::Core)

#QML resources
qt_add_resources(sudoku_qml "qml_resources"
    PREFIX "/"
    FILES
        qml/main.qml
)
#tests
enable_testing()
add_subdirectory(tests)
