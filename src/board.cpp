#include "board.h"

Board::Board() = default;

int Board::get(int row, int col) const {
    if (!isValidIndex(row) || !isValidIndex(col))
        throw std::out_of_range("Index out of range");
    return cells_[row][col];
}

void Board::set(int row, int col, int value) {
    if (!isValidIndex(row) || !isValidIndex(col))
        throw std::out_of_range("Index out of range");
    if (value < 0 || value > 9)
        throw std::invalid_argument("Value must be 0..9");
    cells_[row][col] = value;
}

bool Board::isFixed(int row, int col) const {
    return fixed_[row][col];
}

void Board::setFixed(int row, int col, bool fixed) {
    fixed_[row][col] = fixed;
}
