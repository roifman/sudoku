cmake_minimum_required(VERSION 3.16)

include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/heads/main.zip
)
FetchContent_MakeAvailable(googletest)

add_executable(sudoku_tests
    test_board.cpp
    test_controller.cpp
    $<TARGET_OBJECTS:sudoku_objects>
)

target_include_directories(sudoku_tests PRIVATE ../include)

target_link_libraries(sudoku_tests
    PRIVATE
        gtest_main
        Qt6::Core
)

include(GoogleTest)
gtest_discover_tests(sudoku_tests)
