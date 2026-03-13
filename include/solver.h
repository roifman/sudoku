#pragma once
#include "board.h"

class Solver {
public:
    // solve использует backtracking из Board
    bool solve(Board& board) const {
        return board.solve();
    }
};
