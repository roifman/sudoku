#include "sudokucontroller.h"
#include <exception>
#include <QDebug>
#include <random>
#include <vector>
#include <variant>

SudokuController::SudokuController(QObject* parent)
    : QObject(parent),
      board_(std::make_unique<Board>()),                 // RAII by unique_ptr because only sudokucontroller has access to it
      testSource_(std::make_unique<FilePuzzleSource>("puzzle.txt")),
      solver_(std::make_shared<Solver>())                // shared_ptr not really needed but as an expample 
{
    generatePuzzle();
}

void SudokuController::touchBoard() {
    ++revision_;
    emit boardChanged(); //qt signal
}

int SudokuController::getCell(int row, int col) const {
    return board_->get(row, col);
}

void SudokuController::setCell(int row, int col, int value) {
    try {
        board_->set(row, col, value);
        hasInvalidInput_ = false;
        touchBoard();
    } catch (const std::exception& e) {
        hasInvalidInput_ = true;
        emit invalidInput(QString::fromStdString(e.what()));
    }
}

void SudokuController::solve() {
    if (hasInvalidInput_) {
        emit invalidInput("Cannot solve: board contains invalid values.");
        return;
    }

    if (!solver_->solve(*board_)) {
        emit invalidInput("Puzzle cannot be solved.");
        return;
    }

    touchBoard();
}

void SudokuController::generatePuzzle() {
    board_->clear();

    //std::shuffle
    std::array<int, 9> nums = {1,2,3,4,5,6,7,8,9};
    std::random_device rd;
    std::mt19937 gen(rd());
    std::shuffle(nums.begin(), nums.end(), gen);

    //первую строку случайно  = уникальное решение
    for (int c = 0; c < 9; ++c)
        board_->set(0, c, nums[c]);

    //получаем случайное полное решение
    solver_->solve(*board_);

    //удаляем 40 клеток = пазл
    std::uniform_int_distribution<int> dist(0, 8);

    for (int i = 0; i < 40; ++i) {
        int r = dist(gen);
        int c = dist(gen);
        board_->set(r, c, 0);
    }

    hasInvalidInput_ = false;
    touchBoard();
}

void SudokuController::loadPuzzle() {
    auto loaded = testSource_->load();

    if (!loaded.has_value()) {
        emit invalidInput("Failed to load puzzle from puzzle.txt");
        return;
    }

    *board_ = *loaded;
    hasInvalidInput_ = false;
    touchBoard();
}

void SudokuController::checkSolved() {
    // std::variant + std::visit
    CheckResult result = board_->check();

    std::visit([&](auto&& res) { //switch for types
        using T = std::decay_t<decltype(res)>; //converts reference tp type 
        if constexpr (std::is_same_v<T, CheckOk>) { //constexpr needed for compile-time computation for type based operation
            emit invalidInput("Puzzle solved correctly!");
        } else if constexpr (std::is_same_v<T, CheckError>) {
            emit invalidInput(QString::fromStdString(res.message));
        }
    }, result);
}

void SudokuController::hint() {
    Board solved = *board_;

    if (!solver_->solve(solved)) {
        emit invalidInput("Puzzle cannot be solved.");
        return;
    }

    std::vector<std::pair<int,int>> emptyCells;

    for (int r = 0; r < 9; ++r)
        for (int c = 0; c < 9; ++c)
            if (board_->get(r, c) == 0)
                emptyCells.emplace_back(r, c);

    if (emptyCells.empty()) {
        emit invalidInput("No empty cells left.");
        return;
    }

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(0, static_cast<int>(emptyCells.size()) - 1); //in our limits

    auto [r, c] = emptyCells[dist(gen)];

    try {
        board_->set(r, c, solved.get(r, c));
        touchBoard();
    } catch (const std::exception& e) {
        emit invalidInput(QString::fromStdString(e.what()));
    }
}

void SudokuController::generatePuzzleWithDifficulty(int level) {
    board_->generate(level);
    touchBoard();
}

void SudokuController::generateEasy() {
    generatePuzzleWithDifficulty(1);
}

void SudokuController::generateMedium() {
    generatePuzzleWithDifficulty(2);
}

void SudokuController::generateHard() {
    generatePuzzleWithDifficulty(3);
}
