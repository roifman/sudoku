#include <gtest/gtest.h>
#include "sudokucontroller.h"

TEST(ControllerTest, GenerateCreatesNonEmptyPuzzle) {
    SudokuController c;

    int filled = 0;

    for (int r = 0; r < 9; ++r)
        for (int col = 0; col < 9; ++col)
            if (c.getCell(r, col) != 0)
                filled++;

    EXPECT_GT(filled, 0);
}

TEST(ControllerTest, HintFillsOneCell) {
    SudokuController c;

    c.generatePuzzle();

    int before = 0;
    for (int r = 0; r < 9; ++r)
        for (int col = 0; col < 9; ++col)
            if (c.getCell(r, col) == 0)
                before++;

    c.hint();

    int after = 0;
    for (int r = 0; r < 9; ++r)
        for (int col = 0; col < 9; ++col)
            if (c.getCell(r, col) == 0)
                after++;

    EXPECT_EQ(before - 1, after);
}

TEST(ControllerTest, SolveCompletesPuzzle) {
    SudokuController c;

    c.generatePuzzle();
    c.solve();
    int zeros = 0;
    for (int r = 0; r < 9; ++r)
        for (int col = 0; col < 9; ++col)
            if (c.getCell(r, col) == 0)
                zeros++;

    EXPECT_EQ(zeros, 0);
}
