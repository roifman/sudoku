#include "board.h"
#include <stdexcept>

Board::Board() {
    clear();
}

Board& Board::operator=(const Board& other) {
    if (this != &other) {
        cells_ = other.cells_;
    }
    return *this;
}

void Board::clear() {
    // RAII: доска всегда в корректном состоянии после clear()
    for (int r = 0; r < 9; ++r)
        for (int c = 0; c < 9; ++c)
            cells_[r][c] = 0;
}

int Board::get(int row, int col) const {
    return cells_[row][col];
}

void Board::set(int row, int col, int value) {
    // Современный подход: исключения защищают инварианты модели
    if (!isValid(row, col, value))
        throw std::invalid_argument("Invalid value for this position");

    cells_[row][col] = value;
}

bool Board::isValid(int row, int col, int value) const {
    if (value == 0)
        return true;

    for (int c = 0; c < 9; ++c)
        if (c != col && cells_[row][c] == value)
            return false;

    for (int r = 0; r < 9; ++r)
        if (r != row && cells_[r][col] == value)
            return false;

    int br = (row / 3) * 3;
    int bc = (col / 3) * 3;

    for (int r = br; r < br + 3; ++r)
        for (int c = bc; c < bc + 3; ++c)
            if ((r != row || c != col) && cells_[r][c] == value)
                return false;

    return true;
}

bool Board::solve() {
    return solveRecursive(0, 0);
}

bool Board::solveRecursive(int row, int col) {
    if (row == 9)
        return true;

    int nextRow = (col == 8) ? row + 1 : row;
    int nextCol = (col + 1) % 9;

    if (cells_[row][col] != 0)
        return solveRecursive(nextRow, nextCol);

    for (int v = 1; v <= 9; ++v) {
        cells_[row][col] = v;
        if (isValid(row, col, v) && solveRecursive(nextRow, nextCol))
            return true;
    }

    cells_[row][col] = 0;
    return false;
}

bool Board::isSolved() const {
    for (int r = 0; r < 9; ++r)
        for (int c = 0; c < 9; ++c)
            if (cells_[r][c] == 0)
                return false;

    for (int r = 0; r < 9; ++r)
        for (int c = 0; c < 9; ++c) {
            int v = cells_[r][c];
            const_cast<Board*>(this)->cells_[r][c] = 0;
            bool ok = isValid(r, c, v);
            const_cast<Board*>(this)->cells_[r][c] = v;
            if (!ok)
                return false;
        }

    return true;
}

CheckResult Board::check() const {
    if (!isSolved())
        return CheckError{"Puzzle is not solved correctly."};
    return CheckOk{};
}
