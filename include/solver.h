#pragma once
#include "board.h"

// Solver: отдельный класс для демонстрации разделения ответственности
class Solver {
public:
    // solve использует backtracking из Board
    bool solve(Board& board) const {
        return board.solve();
    }
};
