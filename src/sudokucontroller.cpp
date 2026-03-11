#include "sudokucontroller.h"
#include "filepuzzlesource.h"

SudokuController::SudokuController(QObject* parent)
    : QObject(parent)
{
    source_ = std::make_unique<FilePuzzleSource>("puzzle.txt");
    loadInitial();
}

void SudokuController::loadInitial() {
    auto loaded = source_->load();
    if (!loaded)
        throw std::runtime_error("Failed to load puzzle");
    board_ = std::make_shared<Board>(*loaded);
    emit boardChanged();
}

QVariantList SudokuController::board() const {
    QVariantList list;
    for (int r = 0; r < Board::Size; ++r)
        for (int c = 0; c < Board::Size; ++c)
            list.append(board_->get(r, c));
    return list;
}

void SudokuController::setCell(int row, int col, int value) {
    if (!board_->isFixed(row, col)) {
        board_->set(row, col, value);
        emit boardChanged();
    }
}

void SudokuController::reset() {
    loadInitial();
}
