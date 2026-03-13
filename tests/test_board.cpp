#include <gtest/gtest.h>
#include "board.h"
TEST(BoardTest, ClearResetsAllCells) {
    Board b;
    b.set(0, 0, 5);
    b.clear();

    EXPECT_EQ(b.get(0, 0), 0);
}

TEST(BoardTest, SetRejectsInvalidValue) {
    Board b;
    b.set(0, 0, 5);

    EXPECT_THROW(b.set(0, 1, 5), std::invalid_argument);
}

TEST(BoardTest, SetAcceptsValidValue) {
    Board b;
    b.set(0, 0, 5);

    EXPECT_NO_THROW(b.set(0, 1, 3));
    EXPECT_EQ(b.get(0, 1), 3);
}

TEST(BoardTest, SolveSimplePuzzle) {
    Board b;

    b.set(0, 0, 5);
    b.set(0, 1, 3);
    b.set(0, 2, 0);

    b.set(1, 0, 6);
    b.set(1, 1, 7);
    b.set(1, 2, 2);

    b.set(2, 0, 1);
    b.set(2, 1, 9);
    b.set(2, 2, 8);

    EXPECT_TRUE(b.solve());
    EXPECT_EQ(b.get(0, 2), 4);
}

TEST(BoardTest, CheckDetectsUnsolvedBoard) {
    Board b;
    b.set(0, 0, 5);

    auto result = b.check();

    EXPECT_TRUE(std::holds_alternative<CheckError>(result));
}
