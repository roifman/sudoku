#pragma once

#include <array>
#include <variant>
#include <string>

struct CheckOk {};
struct CheckError {
    std::string message;
};

using CheckResult = std::variant<CheckOk, CheckError>;

class Board {
public:
    Board();

    int get(int row, int col) const;
    void set(int row, int col, int value);
    void clear();

    bool isValid(int row, int col, int value) const;
    bool solve();
    bool isSolved() const;
    CheckResult check() const;

    Board& operator=(const Board& other);

    void generate(int difficulty);

private:
    std::array<std::array<int, 9>, 9> cells_;

    bool solveRecursive(int row, int col);

    void generateSolvedBoard();
    void removeCells(int count);
};
